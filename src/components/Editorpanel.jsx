import React from 'react';
import Editor from '@monaco-editor/react';

export default function EditorPanel({ language, code, setCode, currentTheme }) {
  
  // Maps your theme state to Monaco Editor's native syntax highlighting themes
  const getMonacoTheme = () => {
    if (currentTheme === 'light') return 'vs';
    return 'vs-dark'; // Both dark and intelligent modes use a rich dark code space
  };

  return (
    <div className={`w-full h-[calc(100vh-100px)] rounded-xl overflow-hidden border shadow-xl transition-colors duration-300 ${
      currentTheme === 'light' ? 'bg-white border-slate-200' : 
      currentTheme === 'intelligent' ? 'bg-[#0f172a] border-cyan-500/30' : 'bg-[#0B132B] border-slate-800'
    }`}>
      <Editor
        height="100%"
        language={language || 'cpp'}
        theme={getMonacoTheme()}
        value={code}
        onChange={(value) => setCode(value || '')}
        options={{
          fontSize: 14,
          fontFamily: "'Fira Code', 'Courier New', monospace",
          minimap: { enabled: true },
          scrollBeyondLastLine: false,
          smoothScrolling: true,
          automaticLayout: true,
        }}
      />
    </div>
  );
}
