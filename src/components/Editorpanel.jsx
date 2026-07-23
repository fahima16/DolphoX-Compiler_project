import React from 'react';
import Editor from '@monaco-editor/react';

export default function Editorpanel({ language, code, setCode, theme }) {
  return (
    <div className={`relative w-full h-full rounded-lg border overflow-hidden shadow-2xl ${
      theme === 'dark' ? 'border-slate-800 bg-[#0B132B]' : 'border-slate-300 bg-white'
    }`}>
      
      {/* Centered Dolphin Watermark */}
      <div className="absolute inset-0 flex items-center justify-center pointer-events-none opacity-15 z-10">
        <div className="flex flex-col items-center select-none">
          <span className="text-8xl">🐬</span>
          <span className={`text-xl font-black tracking-widest mt-2 ${theme === 'dark' ? 'text-white' : 'text-slate-900'}`}>
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
            fontSize: 14,
            fontFamily: "'Fira Code', monospace",
            minimap: { enabled: true },
            scrollBeyondLastLine: false,
            automaticLayout: true,
          }}
        />
      </div>

    </div>
  );
}
