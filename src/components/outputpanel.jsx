import React from 'react';

export default function OutputPanel({ output, theme }) {
  return (
    <div className={`w-full h-full rounded-lg border p-3 font-mono text-xs overflow-y-auto shadow-inner ${
      theme === 'dark' ? 'bg-[#090E1A] border-slate-800 text-emerald-400' : 'bg-slate-900 border-slate-700 text-emerald-300'
    }`}>
      <div className="text-slate-500 border-b border-slate-800 pb-1 mb-2 font-semibold">Console Output</div>
      <pre className="whitespace-pre-wrap">{output}</pre>
    </div>
  );
}