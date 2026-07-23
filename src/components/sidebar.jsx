import React from 'react';
import { Folder } from 'lucide-react';

export default function Sidebar({ theme }) {
  return (
    <aside className={`w-56 border-r border-slate-800 p-3 hidden sm:flex flex-col ${theme === 'dark' ? 'bg-[#0B132B]/60' : 'bg-white'}`}>
      <div className="text-xs font-bold text-slate-400 uppercase tracking-wider mb-2">Management</div>
      <div className="flex space-x-2 mb-3 border-b border-slate-700/50 pb-2 text-xs font-semibold">
        <span className="text-cyan-400 border-b-2 border-cyan-400 pb-1 cursor-pointer">Project</span>
        <span className="text-slate-400 hover:text-slate-200 cursor-pointer">Files</span>
      </div>
      <div className="flex items-center space-x-2 text-xs text-slate-300 hover:bg-slate-800/50 p-1.5 rounded cursor-pointer">
        <Folder size={14} className="text-cyan-400" />
        <span>Workspace</span>
      </div>
    </aside>
  );
}