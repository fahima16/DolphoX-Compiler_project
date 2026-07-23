import React from 'react';
import { 
  Play, Bug, Square, Share2, Save, Wand2, 
  Undo2, Redo2, FileText, FolderPlus, Settings, ListTree, 
  Maximize2, Download, RefreshCw, Cpu, Code2, Sun, Moon 
} from 'lucide-react';

export default function Navbar({ theme, setTheme, language, setLanguage, onRun }) {
  return (
    <header className="flex flex-col border-b border-slate-700/50 bg-[#0B132B] text-white">
      
      {/* Top Main Row */}
      <div className="flex items-center justify-between px-4 py-2">
        
        {/* Left: Compact Logo (Dolphin on top, DolphoX text bottom) */}
        <div className="flex items-center space-x-4">
          <div className="flex flex-col items-center">
            <span className="text-2xl leading-none">🐬</span>
            <span className="text-xs font-black tracking-widest bg-gradient-to-r from-cyan-400 to-blue-500 bg-clip-text text-transparent mt-0.5">
              DolphoX
            </span>
          </div>

          {/* Primary Action Buttons */}
          <div className="hidden xl:flex items-center space-x-1.5 border-l border-slate-700 pl-4">
            <button className="p-1.5 bg-slate-800 hover:bg-slate-700 rounded text-slate-300"><FileText size={15} /></button>
            <button className="p-1.5 bg-slate-800 hover:bg-slate-700 rounded text-slate-300"><FolderPlus size={15} /></button>
            <button className="p-1.5 bg-slate-800 hover:bg-slate-700 rounded text-slate-300"><Save size={15} /></button>
            
            <button onClick={onRun} className="flex items-center space-x-1 px-3 py-1.5 bg-emerald-600 hover:bg-emerald-500 text-white rounded text-xs font-semibold shadow ml-2">
              <Play size={13} /> <span>Run</span>
            </button>
            <button className="flex items-center space-x-1 px-3 py-1.5 bg-blue-600 hover:bg-blue-500 text-white rounded text-xs font-semibold">
              <Bug size={13} /> <span>Debug</span>
            </button>
            <button className="flex items-center space-x-1 px-3 py-1.5 bg-rose-600 hover:bg-rose-500 text-white rounded text-xs font-semibold">
              <Square size={13} /> <span>Stop</span>
            </button>
            <button className="flex items-center space-x-1 px-2.5 py-1.5 bg-slate-800 hover:bg-slate-700 text-slate-200 rounded text-xs">
              <Share2 size={13} /> <span>Share</span>
            </button>
            <button className="flex items-center space-x-1 px-2.5 py-1.5 bg-slate-800 hover:bg-slate-700 text-slate-200 rounded text-xs">
              <Save size={13} /> <span>Save</span>
            </button>
            <button className="flex items-center space-x-1 px-2.5 py-1.5 bg-slate-800 hover:bg-slate-700 text-slate-200 rounded text-xs">
              <Wand2 size={13} /> <span>Beautify</span>
            </button>
          </div>
        </div>

        {/* Right Controls: Language Selector & Theme Toggle Switch */}
        <div className="flex items-center space-x-4">
          <div className="flex items-center space-x-2">
            <span className="text-xs text-slate-400 font-medium">Language</span>
            <select 
              value={language} 
              onChange={(e) => setLanguage(e.target.value)}
              className="bg-slate-800 text-cyan-300 border border-slate-700 px-3 py-1 rounded text-xs font-semibold focus:outline-none focus:border-cyan-500 cursor-pointer"
            >
              <option value="c">C</option>
              <option value="cpp">C++</option>
              <option value="java">Java</option>
              <option value="python">Python</option>
            </select>
          </div>

          {/* Switch Toggle for Dark/Light Mode */}
          <div className="flex items-center space-x-2 bg-slate-800/80 px-3 py-1.5 rounded-full border border-slate-700">
            <span className="text-xs text-slate-300 font-medium">Theme</span>
            <button 
              onClick={() => setTheme(theme === 'dark' ? 'light' : 'dark')}
              className={`w-10 h-5 flex items-center rounded-full p-1 transition-colors duration-300 cursor-pointer ${
                theme === 'dark' ? 'bg-cyan-500' : 'bg-slate-600'
              }`}
            >
              <div className={`bg-white w-3.5 h-3.5 rounded-full shadow-md transform transition-transform duration-300 ${
                theme === 'dark' ? 'translate-x-5' : 'translate-x-0'
              }`} />
            </button>
            {theme === 'dark' ? <Moon size={14} className="text-cyan-400" /> : <Sun size={14} className="text-amber-400" />}
          </div>

          <button className="p-1.5 bg-slate-800 hover:bg-slate-700 rounded text-slate-300">
            <Settings size={16} />
          </button>
        </div>

      </div>

      {/* Secondary Sub-Toolbar Row */}
      <div className="flex items-center px-4 py-1.5 bg-[#090E1A] border-t border-slate-800 space-x-2 overflow-x-auto">
        <div className="flex items-center space-x-1 text-slate-400">
          <button className="p-1 hover:bg-slate-800 rounded"><Undo2 size={14} /></button>
          <button className="p-1 hover:bg-slate-800 rounded"><Redo2 size={14} /></button>
          <span className="text-slate-700">|</span>
          <button className="p-1 hover:bg-slate-800 rounded"><FileText size={14} /></button>
          <button className="p-1 hover:bg-slate-800 rounded"><ListTree size={14} /></button>
          <button className="p-1 hover:bg-slate-800 rounded"><Maximize2 size={14} /></button>
          <span className="text-slate-700">|</span>
          <button className="p-1 hover:bg-slate-800 rounded"><Download size={14} /></button>
          <button className="p-1 hover:bg-slate-800 rounded"><RefreshCw size={14} /></button>
          <button className="px-2 py-0.5 text-xs bg-slate-800 hover:bg-slate-700 rounded text-slate-300 font-mono">Laob</button>
          <button className="p-1 hover:bg-slate-800 rounded"><Cpu size={14} /></button>
          <button className="p-1 hover:bg-slate-800 rounded"><Code2 size={14} /></button>
        </div>
      </div>

    </header>
  );
}