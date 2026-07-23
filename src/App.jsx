import React, { useState } from 'react';
import Navbar from './components/Navbar';
import Sidebar from './components/Sidebar';
import Editorpanel from './components/Editorpanel';
import OutputPanel from './components/OutputPanel';

export default function App() {
  const [theme, setTheme] = useState('dark'); // 'dark' or 'light'
  const [language, setLanguage] = useState('cpp');
  const [isSidebarOpen, setIsSidebarOpen] = useState(false);
  const [code, setCode] = useState(
`int main() 
{
    int n = 10;
    for(int i = 1; i <= n; i++) {
        printf("Loop iteration: %d\\n", i);
    }
    
    return 0;
}`
  );
  const [output, setOutput] = useState(
`DolphoX Compiler Output:
Loop iteration: 1
... (omitted lines) ...
Loop iteration: 10
Process exited successfully.`
  );

  const handleRun = () => {
    setOutput(`Running ${language.toUpperCase()} program...\nLoop execution complete.\nProcess exited successfully.`);
  };

  return (
    <div className={`min-h-screen flex flex-col transition-colors duration-300 select-none ${
      theme === 'dark' ? 'bg-[#060D1A] text-white' : 'bg-slate-100 text-slate-900'
    }`}>
      
      {/* Top Navigation & Toolbars */}
      <Navbar 
        theme={theme} 
        setTheme={setTheme} 
        language={language} 
        setLanguage={setLanguage} 
        onRun={handleRun}
        toggleSidebar={() => setIsSidebarOpen(!isSidebarOpen)}
      />

      {/* Main App Workspace Layout (Side-by-Side like the design) */}
      <div className="flex flex-1 overflow-hidden relative">
        
        {/* Left Management Sidebar (Responsive drawer on mobile, static column on desktop) */}
        <Sidebar theme={theme} isOpen={isSidebarOpen} onClose={() => setIsSidebarOpen(false)} />

        {/* Right Coding Workspace Area */}
        <div className="flex-1 flex flex-col p-2 md:p-3 gap-2 md:gap-3 overflow-hidden">
          
          {/* Code Editor Panel */}
          <div className="flex-1 min-h-[260px] md:min-h-[320px]">
            <Editorpanel 
              language={language} 
              code={code} 
              setCode={setCode} 
              theme={theme} 
            />
          </div>

          {/* Console / Output Panel */}
          <div className="h-36 md:h-44">
            <OutputPanel output={output} theme={theme} />
          </div>

        </div>
      </div>

      {/* Bottom Status Bar */}
      <footer className={`flex items-center justify-between px-3 py-1 text-xs border-t ${
        theme === 'dark' ? 'bg-[#060D1A] border-slate-800 text-slate-400' : 'bg-white border-slate-200 text-slate-600'
      }`}>
        <span>Ready</span>
        <span>UTF-8</span>
      </footer>

    </div>
  );
}

