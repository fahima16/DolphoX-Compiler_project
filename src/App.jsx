import React, { useState } from 'react';
import Navbar from './components/Navbar';
import Sidebar from './components/Sidebar';
import Editorpanel from './components/Editorpanel';
import OutputPanel from './components/OutputPanel';

export default function App() {
  const [theme, setTheme] = useState('dark'); // 'dark' or 'light'
  const [language, setLanguage] = useState('cpp');
  const [code, setCode] = useState(
`#include <stdio.h>

int main() {
    int n = 10;
    for(int i = 1; i <= n; i++) {
        printf("Loop iteration: %d\\n", i);
    }
    return 0;
}`
  );
  const [output, setOutput] = useState("DolphoX Compiler Output:\nReady to compile and run loops...");

  const handleRun = () => {
    setOutput(`Running ${language.toUpperCase()} program...\nLoop execution complete.\nProcess exited successfully.`);
  };

  return (
    <div className={`min-h-screen flex flex-col ${theme === 'dark' ? 'dark bg-dolphox-dark text-white' : 'bg-slate-100 text-slate-900'}`}>
      
      {/* Top Navbar */}
      <Navbar 
        theme={theme} 
        setTheme={setTheme} 
        language={language} 
        setLanguage={setLanguage} 
        onRun={handleRun} 
      />

      {/* Main Workspace layout */}
      <div className="flex flex-1 overflow-hidden">
        <Sidebar theme={theme} />
        
        <div className="flex-1 flex flex-col p-3 gap-3 overflow-hidden">
          <div className="flex-1 min-h-[300px]">
            <Editorpanel 
              language={language} 
              code={code} 
              setCode={setCode} 
              theme={theme} 
            />
          </div>
          <div className="h-44">
            <OutputPanel output={output} theme={theme} />
          </div>
        </div>
      </div>
    </div>
  );
}

