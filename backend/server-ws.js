const express = require('express');
const cors = require('cors');
const { spawn } = require('child_process');
const path = require('path');
const fs = require('fs');
const { WebSocketServer } = require('ws');
const pty = require('node-pty');

const app = express();
app.use(cors());
app.use(express.json());

const tempDir = path.join(__dirname, 'temp');
const port = 5000;

const deleteFileIfExists = (filePath) => {
  try {
    if (fs.existsSync(filePath)) {
      fs.unlinkSync(filePath);
    }
  } catch (error) {
    // ignore cleanup failures
  }
};

const cleanupTempDir = () => {
  try {
    if (fs.existsSync(tempDir)) {
      fs.rmSync(tempDir, { recursive: true, force: true });
    }
  } catch (error) {
    // ignore cleanup failures
  }
  fs.mkdirSync(tempDir, { recursive: true });
};

const getTempFilePath = (prefix, ext) => {
  const uniqueSuffix = Date.now().toString(36) + Math.random().toString(36).slice(2, 8);
  return path.join(tempDir, `${prefix}_${uniqueSuffix}${ext}`);
};

const getTempJavaFilePath = (className) => {
  const uniqueSuffix = Date.now().toString(36) + Math.random().toString(36).slice(2, 8);
  const javaDir = path.join(tempDir, `${className}_${uniqueSuffix}`);
  fs.mkdirSync(javaDir, { recursive: true });
  return path.join(javaDir, `${className}.java`);
};

const escapeWindowsArg = (arg) => {
  if (typeof arg !== 'string') return arg;
  return arg.includes(' ') ? `"${arg.replace(/"/g, '\\"')}"` : arg;
};

const normalizeScanfPrompt = (source) => {
  return source.replace(/scanf\(\s*"([^\"]*?)%([^\"]*)"\s*,/g, (match, prefix, suffix) => {
    const prompt = prefix;
    if (!prompt.trim()) {
      return match;
    }
    const escapedPrompt = prompt.replace(/\\/g, '\\\\').replace(/"/g, '\\"');
    return `printf("${escapedPrompt}"); scanf("%${suffix}",`;
  });
};

const ensureOutputDir = () => {
  const outputDir = path.join(tempDir, 'out');
  if (!fs.existsSync(outputDir)) {
    fs.mkdirSync(outputDir, { recursive: true });
  }
  return outputDir;
};

const getExecutablePath = async (name) => {
  return new Promise((resolve, reject) => {
    const proc = spawn('where.exe', [name], { windowsHide: true, shell: false });
    let output = '';
    proc.stdout.on('data', (chunk) => { output += chunk.toString(); });
    proc.stderr.on('data', (chunk) => { output += chunk.toString(); });
    proc.on('error', reject);
    proc.on('close', (code) => {
      if (code !== 0) {
        return reject(new Error(`where.exe failed for ${name}: ${output.trim()}`));
      }
      const paths = output.trim().split(/\r?\n/).map((p) => p.trim()).filter(Boolean);
      const realPath = paths.find((p) => !/\\WindowsApps\\/i.test(p)) || paths[0];
      if (!realPath) {
        return reject(new Error(`Executable ${name} not found`));
      }
      resolve(realPath);
    });
  });
};

const resolvePythonCommand = async () => {
  const candidates = ['python', 'python3', 'py'];
  for (const candidate of candidates) {
    try {
      const exePath = await getExecutablePath(candidate);
      const proc = spawn(exePath, ['--version'], { windowsHide: true, shell: false });
      await new Promise((resolve, reject) => {
        proc.on('error', reject);
        proc.on('close', (code) => (code === 0 ? resolve() : reject(new Error(`Python ${candidate} returned code ${code}`))));
      });
      return exePath;
    } catch {
      continue;
    }
  }
  throw new Error('Python interpreter not found. Please install Python and add it to PATH.');
};

const resolveJavaCommands = async () => {
  try {
    const javacPath = await getExecutablePath('javac');
    const javaPath = await getExecutablePath('java');
    await Promise.all([
      new Promise((resolve, reject) => {
        const proc = spawn(javacPath, ['-version'], { windowsHide: true, shell: false });
        proc.on('error', reject);
        proc.on('close', (code) => (code === 0 ? resolve() : reject(new Error(`javac returned code ${code}`))));
      }),
      new Promise((resolve, reject) => {
        const proc = spawn(javaPath, ['-version'], { windowsHide: true, shell: false });
        proc.on('error', reject);
        proc.on('close', (code) => (code === 0 ? resolve() : reject(new Error(`java returned code ${code}`))));
      }),
    ]);
    return { javac: javacPath, java: javaPath };
  } catch {
    throw new Error('Java JDK not found. Please install JDK and add javac/java to PATH.');
  }
};

cleanupTempDir();

const compileSource = async (language, code) => {
  const selectedLang = (language || 'c').toLowerCase();

  if (selectedLang === 'c') {
    let cCode = normalizeScanfPrompt(code);
    if (!cCode.includes('#include <stdio.h>')) {
      cCode = '#include <stdio.h>\n\n' + cCode;
    }
    const sourceFilePath = getTempFilePath('main', '.c');
    fs.writeFileSync(sourceFilePath, cCode);
    const outputDir = ensureOutputDir();
    const exePath = path.join(outputDir, `main_${path.basename(sourceFilePath).replace(/\.c$/, '')}.exe`);
    deleteFileIfExists(exePath);
    await new Promise((resolve, reject) => {
      const compiler = spawn('gcc', [sourceFilePath, '-o', exePath]);
      let stderr = '';
      compiler.stderr.on('data', (chunk) => { stderr += chunk.toString(); });
      compiler.on('close', (code) => {
        if (code === 0) resolve(); else reject(new Error(stderr || `gcc failed with code ${code}`));
      });
    });
    return { command: exePath, args: [], cleanup: [sourceFilePath, exePath] };
  }

  if (selectedLang === 'cpp' || selectedLang === 'c++') {
    let cppCode = code;
    cppCode = cppCode.replace(/#include\s*<iostream\.h>/g, '#include <iostream>');
    cppCode = cppCode.replace(/#include\s*<conio\.h>/g, '#include <iostream>');
    if (!cppCode.includes('#include <iostream>')) {
      cppCode = '#include <iostream>\nusing namespace std;\n\n' + cppCode;
    }
    const sourceFilePath = getTempFilePath('main', '.cpp');
    fs.writeFileSync(sourceFilePath, cppCode);
    const outputDir = ensureOutputDir();
    const exePath = path.join(outputDir, `main_${path.basename(sourceFilePath).replace(/\.cpp$/, '')}.exe`);
    deleteFileIfExists(exePath);
    await new Promise((resolve, reject) => {
      const compiler = spawn('g++', [sourceFilePath, '-o', exePath]);
      let stderr = '';
      compiler.stderr.on('data', (chunk) => { stderr += chunk.toString(); });
      compiler.on('close', (code) => {
        if (code === 0) resolve(); else reject(new Error(stderr || `g++ failed with code ${code}`));
      });
    });
    return { command: exePath, args: [], cleanup: [sourceFilePath, exePath] };
  }

  if (selectedLang === 'python' || selectedLang === 'py') {
    const pythonCommand = await resolvePythonCommand();
    const sourceFilePath = getTempFilePath('main', '.py');
    fs.writeFileSync(sourceFilePath, code);
    console.log('Python execution prepared:', { pythonCommand, sourceFilePath });
    return { command: pythonCommand, args: [sourceFilePath], cleanup: [sourceFilePath] };
  }

  if (selectedLang === 'java') {
    const { javac, java } = await resolveJavaCommands();
    let javaCode = code;
    const classMatch = javaCode.match(/public\s+class\s+([A-Za-z_][A-Za-z0-9_]*)/);
    const className = classMatch ? classMatch[1] : 'Main';

    if (!classMatch) {
      const lines = javaCode.split(/\r?\n/);
      const declaredVars = new Set();
      const normalizedLines = [];

      for (const rawLine of lines) {
        const line = rawLine.trim();
        if (!line) {
          normalizedLines.push('');
          continue;
        }

        const assignmentMatch = line.match(/^([A-Za-z_][A-Za-z0-9_]*)\s*=\s*/);
        if (assignmentMatch && !/^(int|float|double|char|String|boolean|bool)\b/.test(line)) {
          const varName = assignmentMatch[1];
          if (!declaredVars.has(varName)) {
            normalizedLines.push(`int ${varName};`);
            declaredVars.add(varName);
          }
        }

        normalizedLines.push(line.replace(/\bprint\s*\(/g, 'System.out.println('));
      }

      javaCode = normalizedLines.join('\n');
      javaCode = `public class ${className} {\n    public static void main(String[] args) {\n${javaCode.replace(/^/gm, '        ')}\n    }\n}\n`;
    }

    const sourceFilePath = classMatch ? getTempJavaFilePath(className) : getTempFilePath(className, '.java');
    console.log('Java compile path', { classMatch: !!classMatch, className, sourceFilePath });
    fs.writeFileSync(sourceFilePath, javaCode);
    const javaOutputDir = path.join(tempDir, 'out');
    if (!fs.existsSync(javaOutputDir)) {
      fs.mkdirSync(javaOutputDir, { recursive: true });
    }
    const javaClassFile = path.join(javaOutputDir, `${className}.class`);
    deleteFileIfExists(javaClassFile);
    await new Promise((resolve, reject) => {
      const compiler = spawn(javac, ['-d', javaOutputDir, sourceFilePath]);
      let stderr = '';
      compiler.stderr.on('data', (chunk) => { stderr += chunk.toString(); });
      compiler.on('close', (code) => {
        if (code === 0) resolve(); else reject(new Error(stderr || `javac failed with code ${code}`));
      });
    });
    console.log('Java execution prepared:', { javac, java, sourceFilePath, javaOutputDir, className });
    return { command: java, args: ['-cp', javaOutputDir, className], cleanup: [sourceFilePath, javaClassFile] };
  }

  throw new Error('Unsupported language');
};

const runProcess = (command, args, inputText, timeoutMs = 10000) => new Promise((resolve, reject) => {
  const child = spawn(command, args, { windowsHide: true, shell: false });
  let stdout = '';
  let stderr = '';
  let settled = false;

  const timer = setTimeout(() => {
    if (!settled) {
      child.kill();
      settled = true;
      reject(new Error('Process timed out.'));
    }
  }, timeoutMs);

  child.stdout.on('data', (chunk) => {
    stdout += chunk.toString();
  });

  child.stderr.on('data', (chunk) => {
    stderr += chunk.toString();
  });

  child.on('error', (error) => {
    if (!settled) {
      settled = true;
      clearTimeout(timer);
      reject(error);
    }
  });

  child.on('close', (code) => {
    if (!settled) {
      settled = true;
      clearTimeout(timer);
      if (code === 0) {
        resolve({ stdout, stderr });
      } else {
        reject(new Error(stderr || stdout || `Process exited with code ${code}.`));
      }
    }
  });

  if (inputText !== undefined && inputText !== null) {
    try {
      child.stdin.write(inputText);
    } catch (error) {
      // ignore write errors
    }
  }
  try {
    child.stdin.end();
  } catch (error) {
    // ignore end errors
  }
});

const createPtyProcess = async (language, code, ws) => {
  const compiled = await compileSource(language, code);
  let terminal;
  try {
    terminal = pty.spawn(compiled.command, compiled.args, {
      name: 'xterm-color',
      cols: 80,
      rows: 24,
      cwd: tempDir,
      env: process.env,
    });
  } catch (error) {
    console.error('PTY spawn failed for command:', compiled.command, 'args:', compiled.args, 'error:', error.message);
    if (process.platform === 'win32') {
      const cmdArgs = ['/c', [escapeWindowsArg(compiled.command), ...compiled.args.map(escapeWindowsArg)].join(' ')];
      console.log('Retrying via cmd.exe:', cmdArgs.join(' '));
      terminal = pty.spawn('cmd.exe', cmdArgs, {
        name: 'xterm-color',
        cols: 80,
        rows: 24,
        cwd: tempDir,
        env: process.env,
      });
    } else {
      throw error;
    }
  }

  terminal.onData((data) => {
    if (ws.readyState === ws.OPEN) {
      ws.send(JSON.stringify({ type: 'stdout', payload: data }));
    }
  });

  terminal.onExit(({ exitCode, signal }) => {
    if (ws.readyState === ws.OPEN) {
      ws.send(JSON.stringify({ type: 'done', payload: { exitCode, signal } }));
    }
    compiled.cleanup.forEach(deleteFileIfExists);
  });

  return terminal;
};

app.post('/api/compile', async (req, res) => {
  console.log('compile request received');
  const { code, language, input } = req.body;

  if (!code) {
    return res.status(400).json({ error: 'No code provided.' });
  }

  const inputText = typeof input === 'string' ? input : '';

  try {
    const compiled = await compileSource(language, code);
    const result = await runProcess(compiled.command, compiled.args, inputText);
    compiled.cleanup.forEach(deleteFileIfExists);
    return res.json({ success: true, output: (result.stdout || result.stderr || '').trim() });
  } catch (error) {
    return res.json({ success: false, output: (error.message || String(error)).trim() });
  }
});

const server = app.listen(port, () => {
  console.log(`Backend with interactive terminal running on http://localhost:${port}`);
});

const wss = new WebSocketServer({ server, path: '/terminal' });

wss.on('connection', (ws) => {
  let terminal = null;

  ws.on('message', async (message) => {
    try {
      const data = JSON.parse(message.toString());
      if (data.type === 'run') {
        try {
          terminal = await createPtyProcess(data.language, data.code, ws);
        } catch (compileError) {
          if (ws.readyState === ws.OPEN) {
            ws.send(JSON.stringify({ type: 'stderr', payload: compileError.message || 'Compilation failed.' }));
            ws.send(JSON.stringify({ type: 'done' }));
          }
        }
      }
      if (data.type === 'stdin' && terminal) {
        terminal.write(data.payload);
      }
    } catch (error) {
      if (ws.readyState === ws.OPEN) {
        ws.send(JSON.stringify({ type: 'stderr', payload: error.message || 'Terminal error.' }));
      }
    }
  });

  ws.on('close', () => {
    if (terminal) {
      try { terminal.kill(); } catch (e) { }
    }
  });
});
