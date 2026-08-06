import React, { useState } from 'react';
import Navbar from './components/Navbar';
import Editorpanel from './components/Editorpanel';
import TerminalPanel from './components/TerminalPanel';

export default function App() {
  const [theme, setTheme] = useState('dark');
  const [language, setLanguage] = useState('c');
  const [code, setCode] = useState('int main() {\n    int n = 10;\n    for(int i = 1; i <= n; i++) {\n        printf("Loop iteration: %d\\n", i);\n    }\n    return 0;\n}');
  const [isLoading, setIsLoading] = useState(false);
  const [runToken, setRunToken] = useState(0);
  const [indentSize, setIndentSize] = useState(4);


  const [history, setHistory] = useState([code]);
  const [historyIndex, setHistoryIndex] = useState(0);
  const [sidebarOpen, setSidebarOpen] = useState(false);

  const updateCodeWithHistory = (newCode) => {
    const updatedHistory = history.slice(0, historyIndex + 1);
    updatedHistory.push(newCode);
    setHistory(updatedHistory);
    setHistoryIndex(updatedHistory.length - 1);
    setCode(newCode);
  };

  const handleUndo = () => {
    if (historyIndex > 0) {
      const prevIndex = historyIndex - 1;
      setHistoryIndex(prevIndex);
      setCode(history[prevIndex]);
    }
  };

  const handleRedo = () => {
    if (historyIndex < history.length - 1) {
      const nextIndex = historyIndex + 1;
      setHistoryIndex(nextIndex);
      setCode(history[nextIndex]);
    }
  };

  const handleNewFile = () => {
    updateCodeWithHistory('// Write your code here\nint main() {\n    return 0;\n}\n');
  };

  const handleSave = () => {
    const extensions = { c: 'c', cpp: 'cpp', java: 'java', python: 'py' };
    const ext = extensions[language] || 'txt';
    const blob = new Blob([code], { type: 'text/plain;charset=utf-8' });
    const url = URL.createObjectURL(blob);
    const link = document.createElement('a');
    link.href = url;
    link.download = `main.${ext}`;
    document.body.appendChild(link);
    link.click();
    document.body.removeChild(link);
    URL.revokeObjectURL(url);
  };

  const handleBeautify = () => {
    const cleaned = code
      .split('\n')
      .map(line => line.trimEnd())
      .filter((line, index, arr) => !(line === '' && arr[index - 1] === ''))
      .join('\n')
      .trim();
    updateCodeWithHistory(cleaned);
  };

  const handleRun = (e) => {
    if (e) e.preventDefault();
    setRunToken((prev) => prev + 1);
  };

  return (
    <div className={`h-screen w-screen flex flex-col overflow-hidden ${theme === 'dark' ? 'bg-[#060D1A]' : 'bg-slate-100'}`}>
      
      <Navbar 
        theme={theme} 
        setTheme={setTheme} 
        language={language} 
        setLanguage={setLanguage} 
        indentSize={indentSize} 
        setIndentSize={setIndentSize} 
        onRun={handleRun}
        onNewFile={handleNewFile}
        onSave={handleSave}
        onBeautify={handleBeautify}
        onUndo={handleUndo}
        onRedo={handleRedo}
        toggleSidebar={() => setSidebarOpen(!sidebarOpen)} 
        isLoading={isLoading}
      />
      
      <main className="flex-1 p-3 overflow-hidden">
        <div className="h-full flex flex-col md:flex-row gap-3">
          <Editorpanel 
            language={language} 
            indentSize={indentSize}
            code={code} 
            setCode={updateCodeWithHistory} 
            theme={theme} 
          />
          <TerminalPanel
            language={language}
            code={code}
            runToken={runToken}
            setIsLoading={setIsLoading}
            theme={theme}
          />
        </div>
      </main>

    </div>
  );

}

