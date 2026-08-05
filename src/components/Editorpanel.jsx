import React from 'react';

export default function Editorpanel({ code, setCode, inputText, setInputText, theme, outputCode, outputStatus, isLoading }) {
  const statusStyles = {
    idle: theme === 'dark' ? 'text-slate-400' : 'text-slate-500',
    running: 'text-cyan-400',
    success: 'text-emerald-400',
    error: 'text-rose-400'
  };

  const statusLabels = {
    idle: 'Ready',
    running: 'Running...',
    success: 'Completed',
    error: 'Error'
  };

  const panelText = outputCode || (outputStatus === 'idle' ? 'Click "Run" to see output result here...' : 'No output produced.');

  const handleEditorKeyDown = (event) => {
    if (event.key === 'Tab') {
      event.preventDefault();
      const textarea = event.currentTarget;
      const start = textarea.selectionStart;
      const end = textarea.selectionEnd;
      const indent = '    ';
      const nextValue = `${code.slice(0, start)}${indent}${code.slice(end)}`;
      setCode(nextValue);
      requestAnimationFrame(() => {
        textarea.selectionStart = start + indent.length;
        textarea.selectionEnd = start + indent.length;
      });
      return;
    }

    if (event.key === 'Enter') {
      event.preventDefault();
      const textarea = event.currentTarget;
      const start = textarea.selectionStart;
      const lineStart = code.lastIndexOf('\n', start - 1) + 1;
      const linePrefix = code.slice(lineStart, start);
      const indentMatch = linePrefix.match(/^\s*/)[0];
      const trimmed = linePrefix.trim();
      let newIndent = indentMatch;

      if (trimmed.endsWith('{')) {
        newIndent += '    ';
      } else if (trimmed === '}' && indentMatch.length >= 4) {
        newIndent = indentMatch.slice(0, -4);
      }

      const nextValue = `${code.slice(0, start)}\n${newIndent}${code.slice(start)}`;
      setCode(nextValue);
      requestAnimationFrame(() => {
        textarea.selectionStart = start + 1 + newIndent.length;
        textarea.selectionEnd = start + 1 + newIndent.length;
      });
    }
  };

  return (
    <div className="w-full h-full flex flex-col md:flex-row gap-3">
      <div className={`flex-1 rounded-lg border overflow-hidden shadow-2xl ${theme === 'dark' ? 'border-slate-800 bg-[#0B1426]' : 'border-slate-300 bg-white'}`}>
        <textarea
          value={code}
          onChange={(e) => setCode(e.target.value || '')}
          onKeyDown={handleEditorKeyDown}
          spellCheck={false}
          className={`w-full h-full resize-none border-0 outline-none p-4 font-mono text-sm leading-6 ${theme === 'dark' ? 'bg-[#0B1426] text-slate-100' : 'bg-white text-slate-900'}`}
          style={{ fontFamily: "'Fira Code', 'Courier New', monospace" }}
        />
      </div>

      <div className={`w-full md:w-1/3 flex flex-col rounded-lg border overflow-hidden shadow-2xl ${theme === 'dark' ? 'border-slate-800 bg-[#060D1A] text-slate-200' : 'border-slate-300 bg-slate-900 text-white'}`}>
        <div className={`px-4 py-2 border-b text-xs font-bold uppercase tracking-wider ${theme === 'dark' ? 'border-slate-800 bg-[#0b1426] text-slate-400' : 'border-slate-700 bg-slate-800 text-slate-300'}`}>
          <div className="mb-2">Input (stdin)</div>
          <textarea
            value={inputText}
            onChange={(e) => setInputText(e.target.value)}
            placeholder="Enter input for your program here"
            className={`w-full h-20 resize-none rounded border p-2 text-sm font-mono ${theme === 'dark' ? 'border-slate-700 bg-[#0B1426] text-slate-100' : 'border-slate-600 bg-slate-800 text-white'}`}
          />
        </div>
        <div className={`px-4 py-2 border-b flex justify-between items-center text-xs font-bold uppercase tracking-wider ${theme === 'dark' ? 'border-slate-800 bg-[#0b1426] text-slate-400' : 'border-slate-700 bg-slate-800 text-slate-300'}`}>
          <span>Terminal Output</span>
          <span className={`flex items-center gap-2 ${statusStyles[outputStatus] || statusStyles.idle}`}>
            {isLoading && <span className="inline-block h-2 w-2 rounded-full bg-cyan-400 animate-pulse" />}
            <span>{isLoading ? 'Executing...' : statusLabels[outputStatus] || 'Ready'}</span>
          </span>
        </div>

        <div id="terminal-output" className={`p-4 flex-1 font-mono text-sm overflow-auto whitespace-pre-wrap leading-relaxed ${outputStatus === 'error' ? 'text-rose-400' : outputStatus === 'success' ? 'text-emerald-400' : 'text-slate-300'}`} role="log">
          {panelText}
        </div>
      </div>
    </div>
  );
}