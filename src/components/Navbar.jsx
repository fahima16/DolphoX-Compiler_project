import React from 'react';
import { Play, Bug, Square, Share2, Save, Wand2, Sun, Moon } from 'lucide-react';

export default function Navbar({ theme, setTheme, language, setLanguage, onRun }) {
  return (
    <header className="flex items-center justify-between px-4 py-2 border-b border-slate-700/50 bg-[#0B132B]/90 backdrop-blur-md">
      
      {/* Compact Logo: Dolphin on top, DolphoX text below */}
      <div className="flex items-center space-x-3">
        <div className="flex flex-col items-center">
          <span className="text-2xl">🐬</span>
          <span className="text-sm font-extrabold tracking-widest bg-gradient-to-r from-cyan-400 to-blue-500 bg-clip-text text-transparent">
            DolphoX
          </span>
        </div>

        {/* Action Toolbar */}
        <div className="hidden md:flex items-center space-x-1.5 ml-4 border-l border-slate-700 pl-4">
          <button onClick={onRun} className="flex items-center space-x-1 px-3 py-1.5 bg-emerald-600 hover:bg-emerald-500 text-white rounded text-xs font-semibold shadow">
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

      {/* Right Controls: Language Dropdown & Theme Toggle */}
      <div className="flex items-center space-x-4">
        <div className="flex items-center space-x-2">
          <span className="text-xs text-slate-400 font-medium">Language</span>
          <select 
            value={language} 
            onChange={(e) => setLanguage(e.target.value)}
            className="bg-slate-800 text-cyan-300 border border-slate-700 px-3 py-1 rounded text-xs font-semibold focus:outline-none focus:border-cyan-500"
          >
            <option value="c">C</option>
            <option value="cpp">C++</option>
            <option value="java">Java</option>
            <option value="python">Python</option>
          </select>
        </div>

        {/* Theme Switcher Button */}
        <button 
          onClick={() => setTheme(theme === 'dark' ? 'light' : 'dark')}
          className="p-2 rounded-full bg-slate-800 hover:bg-slate-700 text-cyan-400 transition"
          title="Toggle Theme"
        >
          {theme === 'dark' ? <Sun size={16} /> : <Moon size={16} />}
        </button>

        
      </div>

    </header>
  );
}