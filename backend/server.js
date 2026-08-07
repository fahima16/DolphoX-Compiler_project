const express = require('express');
const cors = require('cors');
const { spawn } = require('child_process');
const path = require('path');
const fs = require('fs');

const app = express();
app.use(cors());
app.use(express.json());

// টেম্পোরারি ফোল্ডার না থাকলে বানিয়ে নেবে
const tempDir = path.join(__dirname, 'temp');

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

const cleanupStaleArtifacts = (filePath) => {
    deleteFileIfExists(filePath);
};

const { normalizeScanfPrompt } = require('./scanf-normalizer');

const ensureOutputDir = () => {
    const outputDir = path.join(tempDir, 'out');
    if (!fs.existsSync(outputDir)) {
        fs.mkdirSync(outputDir, { recursive: true });
    }
    return outputDir;
};

cleanupTempDir();


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
            // ignore write errors for empty input
        }
    }
    try {
        child.stdin.end();
    } catch (error) {
        // ignore end errors
    }
});

app.post('/api/compile', async (req, res) => {
    console.log('compile request received');
    const { code, language, input } = req.body;

    if (!code) {
        return res.status(400).json({ error: 'No code provided.' });
    }

    const selectedLang = (language || 'c').toLowerCase();
    const inputText = typeof input === 'string' ? input : '';

    try {
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
            await runProcess('gcc', [sourceFilePath, '-o', exePath], '');
            const result = await runProcess(exePath, [], inputText);
            deleteFileIfExists(sourceFilePath);
            deleteFileIfExists(exePath);
            return res.json({ success: true, output: (result.stdout || result.stderr || '').trim() });
        }

        if (selectedLang === 'cpp' || selectedLang === 'c++') {
            let cppCode = normalizeScanfPrompt(code);
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
            await runProcess('g++', [sourceFilePath, '-o', exePath], '');
            const result = await runProcess(exePath, [], inputText);
            deleteFileIfExists(sourceFilePath);
            deleteFileIfExists(exePath);
            return res.json({ success: true, output: (result.stdout || result.stderr || '').trim() });
        }

        if (selectedLang === 'python' || selectedLang === 'py') {
            const sourceFilePath = getTempFilePath('main', '.py');
            fs.writeFileSync(sourceFilePath, code);
            const result = await runProcess('python', [sourceFilePath], inputText);
            deleteFileIfExists(sourceFilePath);
            return res.json({ success: true, output: (result.stdout || result.stderr || '').trim() });
        }

        if (selectedLang === 'java') {
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

                    const assignmentMatch = line.match(/^([A-Za-z_][A-Za-z0-9_]*)\s*=/);
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

            const sourceFilePath = getTempFilePath(className, '.java');
            fs.writeFileSync(sourceFilePath, javaCode);
            const javaOutputDir = path.join(tempDir, 'out');
            if (!fs.existsSync(javaOutputDir)) {
                fs.mkdirSync(javaOutputDir, { recursive: true });
            }
            const javaClassFile = path.join(javaOutputDir, `${className}.class`);
            deleteFileIfExists(javaClassFile);
            await runProcess('javac', ['-d', javaOutputDir, sourceFilePath], '');
            const result = await runProcess('java', ['-cp', javaOutputDir, className], inputText);
            deleteFileIfExists(sourceFilePath);
            deleteFileIfExists(javaClassFile);
            return res.json({ success: true, output: (result.stdout || result.stderr || '').trim() });
        }

        return res.status(400).json({ error: 'Unsupported language' });
    } catch (error) {
        return res.json({ success: false, output: (error.message || String(error)).trim() });
    }
});

app.listen(5000, () => {
    console.log('Backend connected with custom compiler-core on http://localhost:5000');
});