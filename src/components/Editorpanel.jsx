import React from 'react';
import Editor from '@monaco-editor/react';

export default function Editorpanel({ language, code, setCode, theme }) {
  return (
    <div className={`relative w-full h-full rounded-lg border overflow-hidden shadow-2xl ${
      theme === 'dark' ? 'border-slate-800 bg-[#0B1426]' : 'border-slate-300 bg-white'
    }`}>
      
      {/* Centered Watermark with Dolphin Graphic & DolphoX Label */}
      <div className="absolute inset-0 flex items-center justify-center pointer-events-none opacity-15 z-10">
        <div className="flex flex-col items-center select-none">
          <span className="text-7xl md:text-9xl">🐬</span>
          <span className={`text-lg md:text-xl font-black tracking-widest mt-1 ${
            theme === 'dark' ? 'text-white' : 'text-slate-900'
          }`}>
            DolphoX
          </span>
        </div>
      </div>

      {/* Monaco Code Editor */}
      <div className="relative z-0 w-full h-full">
        <Editor
          height="100%"
          language={language === 'c' ? 'cpp' : language}
          theme={theme === 'dark' ? 'vs-dark' : 'vs'}
          value={code}
          onChange={(value) => setCode(value || '')}
          options={{
            fontSize: 13,
            fontFamily: "'Fira Code', 'Courier New', monospace",
            minimap: { enabled: true },
            scrollBeyondLastLine: false,
            automaticLayout: true,
            padding: { top: 12 },
          }}
        />
      </div>

    </div>
  );
}