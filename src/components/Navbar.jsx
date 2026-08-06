import React, { useState } from 'react';
import { 
  Play, Bug, Square, Share2, Save, Wand2, 
  Undo2, Redo2, FileText, FolderPlus, Settings, ListTree, 
  Maximize2, Download, RefreshCw, Cpu, Code2, Sun, Moon, Menu 
} from 'lucide-react';

export default function Navbar({ 
  theme, setTheme, language, setLanguage, indentSize, setIndentSize, onRun, toggleSidebar,
  onNewFile, onSave, onBeautify, onUndo, onRedo 
}) {
  return (
    <header className={`flex flex-col border-b transition-colors duration-300 ${
      theme === 'dark' ? 'bg-[#0B1426] border-slate-800 text-white' : 'bg-white border-slate-200 text-slate-800'
    }`}>
      
      {/* Primary Top Action Bar */}
      <div className="flex items-center justify-between px-3 md:px-4 py-2">

        
        <div className="flex items-center space-x-3">


          <button onClick={toggleSidebar} className="md:hidden p-1.5 rounded bg-slate-800 text-white hover:bg-slate-700 cursor-pointer">
            <Menu size={18} />
          </button>

          <div className="flex flex-col items-center select-none">
            <span className="text-2xl leading-none">🐬</span>
            <span className="text-xs font-black tracking-widest bg-gradient-to-r from-cyan-400 to-blue-500 bg-clip-text text-transparent mt-0.5">
              DolphoX
            </span>
          </div>



          <div className="flex flex-wrap items-center gap-1.5 border-l border-slate-700/50 pl-4">
            <button onClick={onNewFile} className="p-1.5 bg-slate-800 hover:bg-slate-700 rounded text-slate-300 shadow cursor-pointer" title="New File"><FileText size={15} /></button>
            <button onClick={onNewFile} className="p-1.5 bg-slate-800 hover:bg-slate-700 rounded text-slate-300 shadow cursor-pointer" title="New Project"><FolderPlus size={15} /></button>
            <button onClick={onSave} className="p-1.5 bg-slate-800 hover:bg-slate-700 rounded text-slate-300 shadow cursor-pointer" title="Save"><Save size={15} /></button>
            
            <button
              type="button"
              onClick={(event) => {
                event.preventDefault();
                event.stopPropagation();
                onRun(event);
              }}
              title="Run"
              aria-label="Run"
              className="flex items-center space-x-1 px-3 py-1.5 bg-emerald-600 hover:bg-emerald-500 text-white rounded text-xs font-semibold shadow ml-2 cursor-pointer"
            >
              <Play size={13} /> <span>Run</span>
            </button>
            <button className="flex items-center space-x-1 px-3 py-1.5 bg-blue-600 hover:bg-blue-500 text-white rounded text-xs font-semibold shadow cursor-pointer">
              <Bug size={13} /> <span>Debug</span>
            </button>
            <button className="flex items-center space-x-1 px-3 py-1.5 bg-rose-600 hover:bg-rose-500 text-white rounded text-xs font-semibold shadow cursor-pointer">
              <Square size={13} /> <span>Stop</span>
            </button>
            <button onClick={onSave} className="flex items-center space-x-1 px-2.5 py-1.5 bg-slate-800 hover:bg-slate-700 text-slate-200 rounded text-xs shadow cursor-pointer">
              <Share2 size={13} /> <span>Share</span>
            </button>
            <button onClick={onSave} className="flex items-center space-x-1 px-2.5 py-1.5 bg-slate-800 hover:bg-slate-700 text-slate-200 rounded text-xs shadow cursor-pointer">
              <Save size={13} /> <span>Save</span>
            </button>
            <button onClick={onBeautify} className="flex items-center space-x-1 px-2.5 py-1.5 bg-slate-800 hover:bg-slate-700 text-slate-200 rounded text-xs shadow cursor-pointer">
              <Wand2 size={13} /> <span>Beautify</span>
            </button>
          </div>
        </div>


        <div className="flex items-center space-x-3 md:space-x-4">


          <div className="flex items-center space-x-1.5">
            <span className="text-xs text-slate-400 font-medium hidden sm:inline">Language</span>
            <select 
              value={language} 
              onChange={(e) => setLanguage(e.target.value)}
              className="bg-slate-800 text-cyan-300 border border-slate-700 px-2.5 py-1 rounded text-xs font-semibold focus:outline-none focus:border-cyan-500 cursor-pointer shadow"
            >
              <option value="c">C</option>
              <option value="cpp">C++</option>
              <option value="java">Java</option>
              <option value="python">Python</option>
            </select>
          </div>
          <div className="flex items-center space-x-1.5 border-l border-slate-700/50 pl-4">
            <span className="text-xs text-slate-400 font-medium hidden sm:inline">Indent</span>
            <button
              type="button"
              onClick={() => setIndentSize(Math.max(1, indentSize - 1))}
              className="px-2 py-1 bg-slate-800 hover:bg-slate-700 rounded text-slate-200 text-xs font-semibold"
            >
              -
            </button>
            <span className="min-w-[1.5rem] text-center text-xs font-semibold text-slate-200">{indentSize}</span>
            <button
              type="button"
              onClick={() => setIndentSize(Math.min(8, indentSize + 1))}
              className="px-2 py-1 bg-slate-800 hover:bg-slate-700 rounded text-slate-200 text-xs font-semibold"
            >
              +
            </button>
          </div>


          <div className="flex items-center space-x-2 bg-slate-800/80 px-2.5 py-1 rounded-full border border-slate-700 shadow-inner">
            <span className="text-[11px] text-slate-300 font-medium hidden sm:inline">Theme toggle</span>
            <button 
              onClick={() => setTheme(theme === 'dark' ? 'light' : 'dark')}
              className={`w-9 h-4.5 flex items-center rounded-full p-0.5 transition-colors duration-300 cursor-pointer ${
                theme === 'dark' ? 'bg-cyan-500' : 'bg-slate-600'
              }`}
            >
              <div className={`bg-white w-3.5 h-3.5 rounded-full shadow-md transform transition-transform duration-300 ${
                theme === 'dark' ? 'translate-x-4.5' : 'translate-x-0'
              }`} />
            </button>
            {theme === 'dark' ? <Moon size={13} className="text-cyan-400" /> : <Sun size={13} className="text-amber-400" />}
          </div>

          <button className="p-1.5 bg-slate-800 hover:bg-slate-700 rounded text-slate-300 hidden sm:block cursor-pointer">
            <Settings size={15} />
          </button>
        </div>

      </div>

      {/* Secondary Sub-Toolbar Row */}
      <div className={`hidden md:flex items-center px-4 py-1.5 border-t space-x-2 overflow-x-auto ${
        theme === 'dark' ? 'bg-[#060D1A] border-slate-800' : 'bg-slate-50 border-slate-200'
      }`}>
        <div className="flex items-center space-x-1 text-slate-400">
          <button onClick={onUndo} className="p-1 hover:bg-slate-800 hover:text-white rounded transition cursor-pointer" title="Undo"><Undo2 size={14} /></button>
          <button onClick={onRedo} className="p-1 hover:bg-slate-800 hover:text-white rounded transition cursor-pointer" title="Redo"><Redo2 size={14} /></button>
          
          <span className="text-slate-700">|</span>
          
          <button onClick={onNewFile} className="p-1 hover:bg-slate-800 hover:text-white rounded transition cursor-pointer" title="New File"><FileText size={14} /></button>
          <button onClick={() => alert('Outline panel active')} className="p-1 hover:bg-slate-800 hover:text-white rounded transition cursor-pointer" title="Outline"><ListTree size={14} /></button>
          
          <button 
            onClick={() => {
              if (!document.fullscreenElement) {
                document.documentElement.requestFullscreen();
              } else {
                document.exitFullscreen();
              }
            }} 
            className="p-1 hover:bg-slate-800 hover:text-white rounded transition cursor-pointer" 
            title="Fullscreen"
          >
            <Maximize2 size={14} />
          </button>
          
          <span className="text-slate-700">|</span>
          
          <button onClick={onSave} className="p-1 hover:bg-slate-800 hover:text-white rounded transition cursor-pointer" title="Download Code"><Download size={14} /></button>
          <button onClick={() => window.location.reload()} className="p-1 hover:bg-slate-800 hover:text-white rounded transition cursor-pointer" title="Reset Workspace"><RefreshCw size={14} /></button>
          
          <span className="px-2 py-0.5 text-xs bg-slate-800 text-slate-300 font-mono rounded">Lab</span>
          
          <button className="p-1 hover:bg-slate-800 hover:text-white rounded transition cursor-pointer" title="CPU Stats"><Cpu size={14} /></button>
          <button className="p-1 hover:bg-slate-800 hover:text-white rounded transition cursor-pointer" title="Code Analysis"><Code2 size={14} /></button>
        </div>
      </div>

    </header>
  );
}