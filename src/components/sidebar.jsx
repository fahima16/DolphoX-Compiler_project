import React, { useState } from 'react';
import { Folder, ChevronRight, X } from 'lucide-react';

export default function Sidebar({ theme, isOpen, onClose }) {
  const [activeTab, setActiveTab] = useState('project');

  return (
    <>
      {/* Mobile Backdrop Overlay */}
      {isOpen && (
        <div 
          className="fixed inset-0 bg-black/50 z-20 md:hidden"
          onClick={onClose}
        />
      )}

      {/* Sidebar Container */}
      <aside className={`absolute md:relative z-30 top-0 left-0 h-full w-56 border-r p-3 flex flex-col transition-transform duration-300 ${
        isOpen ? 'translate-x-0' : '-translate-x-full md:translate-x-0'
      } ${
        theme === 'dark' ? 'bg-[#0B1426] border-slate-800 text-slate-300' : 'bg-white border-slate-200 text-slate-700'
      }`}>
        
        {/* Header Title */}
        <div className="flex items-center justify-between mb-2">
          <span className="text-xs font-bold text-slate-400 uppercase tracking-wider">Management</span>
          <button onClick={onClose} className="md:hidden text-slate-400 hover:text-white">
            <X size={16} />
          </button>
        </div>

        {/* Tab Switcher (Project / Files) */}
        <div className="flex space-x-2 mb-3 border-b border-slate-700/50 pb-2 text-xs font-semibold">
          <button 
            onClick={() => setActiveTab('project')}
            className={`pb-1 cursor-pointer transition-colors ${
              activeTab === 'project' ? 'text-cyan-400 border-b-2 border-cyan-400' : 'text-slate-400 hover:text-slate-200'
            }`}
          >
            Project
          </button>
          <button 
            onClick={() => setActiveTab('files')}
            className={`pb-1 cursor-pointer transition-colors ${
              activeTab === 'files' ? 'text-cyan-400 border-b-2 border-cyan-400' : 'text-slate-400 hover:text-slate-200'
            }`}
          >
            Files
          </button>
        </div>

        {/* Workspace Folder Tree View */}
        <div className="space-y-1">
          <div className="flex items-center space-x-2 text-xs text-cyan-300 bg-slate-800/40 p-1.5 rounded cursor-pointer border border-cyan-500/20 shadow-sm">
            <Folder size={14} className="text-cyan-400" />
            <span className="font-medium">Workspace</span>
          </div>
        </div>

      </aside>
    </>
  );
}