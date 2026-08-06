import React from 'react';

export default function Editorpanel({ language, indentSize, code, setCode, theme }) {
  const PAIRS = { '{': '}', '(': ')', '[': ']' };
  const indent = ' '.repeat(indentSize);

  const handleEditorKeyDown = (event) => {
    const textarea = event.currentTarget;
    const start = textarea.selectionStart;
    const end = textarea.selectionEnd;

    if (event.key === 'Tab') {
      event.preventDefault();

      if (event.shiftKey) {
        const lineStart = code.lastIndexOf('\n', start - 1) + 1;
        const beforeCursor = code.slice(lineStart, start);
        if (beforeCursor.endsWith(indent)) {
          const nextValue = `${code.slice(0, start - indent.length)}${code.slice(start)}`;
          setCode(nextValue);
          requestAnimationFrame(() => {
            textarea.selectionStart = start - indent.length;
            textarea.selectionEnd = end - indent.length;
          });
          return;
        }
      }

      event.preventDefault();
      const nextValue = `${code.slice(0, start)}${indent}${code.slice(end)}`;
      setCode(nextValue);
      requestAnimationFrame(() => {
        textarea.selectionStart = start + indent.length;
        textarea.selectionEnd = start + indent.length;
      });
      return;
    }

    if (event.key === 'Backspace' && start === end) {
      const beforeCursor = code.slice(0, start);
      const afterCursor = code.slice(end);

      if (beforeCursor.endsWith(indent)) {
        event.preventDefault();
        const nextValue = `${code.slice(0, start - indent.length)}${afterCursor}`;
        setCode(nextValue);
        requestAnimationFrame(() => {
          textarea.selectionStart = start - indent.length;
          textarea.selectionEnd = start - indent.length;
        });
        return;
      }

      if (beforeCursor.endsWith('{') && afterCursor.startsWith('}')) {
        event.preventDefault();
        const nextValue = `${code.slice(0, start - 1)}${afterCursor.slice(1)}`;
        setCode(nextValue);
        requestAnimationFrame(() => {
          textarea.selectionStart = start - 1;
          textarea.selectionEnd = start - 1;
        });
        return;
      }
    }

    if (event.key in PAIRS && !event.ctrlKey && !event.altKey && !event.metaKey) {
      event.preventDefault();
      const closing = PAIRS[event.key];
      const nextValue = `${code.slice(0, start)}${event.key}${closing}${code.slice(end)}`;
      setCode(nextValue);
      requestAnimationFrame(() => {
        textarea.selectionStart = start + 1;
        textarea.selectionEnd = start + 1;
      });
      return;
    }

    if (event.key === '}') {
      const nextChar = code.charAt(start);
      if (nextChar === '}') {
        event.preventDefault();
        requestAnimationFrame(() => {
          textarea.selectionStart = start + 1;
          textarea.selectionEnd = start + 1;
        });
        return;
      }
    }

    if (event.key === 'Enter') {
      event.preventDefault();
      const lineStart = code.lastIndexOf('\n', start - 1) + 1;
      const linePrefix = code.slice(lineStart, start);
      const indentMatch = linePrefix.match(/^\s*/)[0];
      const trimmed = linePrefix.trim();
      let newIndent = indentMatch;

      const shouldIndent = trimmed.endsWith('{') || (language === 'python' && trimmed.endsWith(':'));
      if (shouldIndent) {
        newIndent += indent;
      } else if (trimmed === '}' && indentMatch.length >= indent.length) {
        newIndent = indentMatch.slice(0, -indent.length);
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
    <div className={`w-full h-full rounded-lg border overflow-hidden shadow-2xl ${theme === 'dark' ? 'border-slate-800 bg-[#0B1426]' : 'border-slate-300 bg-white'}`}>
      <textarea
        value={code}
        onChange={(e) => setCode(e.target.value || '')}
        onKeyDown={handleEditorKeyDown}
        spellCheck={false}
        className={`w-full h-full resize-none border-0 outline-none p-4 font-mono text-sm leading-6 ${theme === 'dark' ? 'bg-[#0B1426] text-slate-100' : 'bg-white text-slate-900'}`}
        style={{ fontFamily: "'Fira Code', 'Courier New', monospace" }}
      />
    </div>
  );
}