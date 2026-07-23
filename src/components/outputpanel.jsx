import React from 'react';

export default function OutputPanel({ output, theme }) {
  return (
    <div className={`w-full h-full rounded-lg border p-3 font-mono text-xs overflow-y-auto shadow-inner ${
      theme === 'dark' ? 'bg-[#040810] border-slate-800 text-emerald-400' : 'bg-slate-900 border-slate-700 text-emerald-300'
    }`}>
      <div className="text-slate-500 border-b border-slate-800 pb-1 mb-2 font-semibold flex items-center justify-between">
        <span>Console Output</span>
        <span className="text-[10px] text-emerald-500/70">● Status: Active</span>
      </div>
      <pre className="whitespace-pre-wrap leading-relaxed">{output}</pre>
    </div>
  );
}