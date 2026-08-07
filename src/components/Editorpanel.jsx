import React, { useEffect, useRef, useState } from 'react';

export default function Editorpanel({ language, indentSize, code, setCode, theme }) {
  const PAIRS = { '{': '}', '(': ')', '[': ']' };
  const indent = ' '.repeat(indentSize);
  const [lineCount, setLineCount] = useState(36);
  const containerRef = useRef(null);
  const textareaRef = useRef(null);
  const gutterRef = useRef(null);

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
  useEffect(() => {
    const lines = code.split('\n').length;
    setLineCount(Math.max(36, lines));
  }, [code]);

  return (
    <div
      ref={containerRef}
      className={`relative h-full w-full overflow-hidden rounded-lg border shadow-2xl ${theme === 'dark' ? 'border-slate-800 bg-[#0B1426]' : 'border-slate-300 bg-white'}`}
    >
      {/* Left line-number gutter */}
      <div ref={gutterRef} className="absolute left-0 top-0 bottom-0 w-12 select-none border-r border-slate-700/20 bg-transparent overflow-hidden">
        <div className="text-xs leading-6 text-slate-400 font-mono" style={{ padding: '16px 8px 8px 8px' }}>
          {Array.from({ length: lineCount }).map((_, i) => (
            <div key={i} className="h-6 text-right pr-1 leading-6">{i + 1}</div>
          ))}
        </div>
      </div>

      {/* Watermark centered */}
      <div className="pointer-events-none absolute inset-0 flex items-center justify-center">
        <div className="text-[10rem] opacity-5 leading-none select-none">🐬</div>
      </div>

      <textarea
        ref={textareaRef}
        value={code}
        onChange={(e) => setCode(e.target.value || '')}
        onScroll={() => {
          if (gutterRef.current && textareaRef.current) {
            gutterRef.current.scrollTop = textareaRef.current.scrollTop;
          }
        }}
        onKeyDown={handleEditorKeyDown}
        spellCheck={false}
        className={`relative z-0 h-full w-full resize-none border-0 font-mono text-sm outline-none ${theme === 'dark' ? 'bg-transparent text-slate-100' : 'bg-transparent text-slate-900'}`}
        style={{ fontFamily: "'Fira Code', 'Courier New', monospace", padding: '16px', paddingLeft: '76px', lineHeight: '24px' }}
      />
    </div>
  );
}