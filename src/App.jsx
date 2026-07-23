import React, { useState } from 'react';
import Navbar from './components/Navbar';
import EditorPanel from './components/EditorPanel';

export default function App() {
  // Theme can be 'dark', 'light', or 'intelligent'
  const [theme, setTheme] = useState('dark');
  const [code, setCode] = useState('// Welcome to DolphoX\nconsole.log("Hello from Dolphin AI!");');
  const [language, setLanguage] = useState('cpp');

  return (
    <div className={`min-h-screen transition-colors duration-300 ${theme === 'light' ? 'light' : 'dark'}`}>
      {/* Navbar with the Theme Switcher */}
      <Navbar currentTheme={theme} setTheme={setTheme} />

      {/* Main Editor View */}
      <main className="p-4">
        <EditorPanel 
          language={language} 
          code={code} 
          setCode={setCode} 
          currentTheme={theme} 
        />
      </main>
    </div>
  );
}
