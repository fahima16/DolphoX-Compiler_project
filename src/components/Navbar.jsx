import React from 'react';
import { Sun, Moon, Sparkles } from 'lucide-react';

export default function Navbar({ currentTheme, setTheme }) {
  return (
    <header className="flex items-center justify-between px-6 py-4 border-b border-slate-200 dark:border-slate-800 bg-white/80 dark:bg-[#0B132B]/80 backdrop-blur-md transition-colors duration-300">
      
      {/* Brand Logo */}
      <div className="flex items-center space-x-3">
        <div className="w-9 h-9 rounded-xl bg-gradient-to-tr from-cyan-500 to-blue-600 flex items-center justify-center shadow-lg shadow-cyan-500/30 text-white font-bold text-lg">
          🐬
        </div>
        <span className="text-xl font-black tracking-wider bg-gradient-to-r from-cyan-400 to-blue-600 bg-clip-text text-transparent">
          DolphoX
        </span>
      </div>

      {/* Theme Switcher Options */}
      <div className="flex items-center bg-slate-100 dark:bg-slate-900 p-1 rounded-full border border-slate-200 dark:border-slate-800 shadow-inner">
        
        {/* Light Mode */}
        <button
          onClick={() => setTheme('light')}
          className={`flex items-center space-x-1 px-3 py-1.5 rounded-full text-xs font-semibold transition-all ${
            currentTheme === 'light' 
              ? 'bg-white text-slate-900 shadow-md' 
              : 'text-slate-500 hover:text-slate-900 dark:hover:text-white'
          }`}
        >
          <Sun size={14} />
          <span>Light</span>
        </button>

        {/* Intelligent Center Mode */}
        <button
          onClick={() => setTheme('intelligent')}
          className={`flex items-center space-x-1 px-3 py-1.5 rounded-full text-xs font-semibold transition-all ${
            currentTheme === 'intelligent' 
              ? 'bg-gradient-to-r from-cyan-500 to-blue-600 text-white shadow-md shadow-cyan-500/20' 
              : 'text-slate-500 hover:text-slate-900 dark:hover:text-white'
          }`}
        >
          <Sparkles size={14} />
          <span>Intelligent</span>
        </button>

        {/* Dark Mode */}
        <button
          onClick={() => setTheme('dark')}
          className={`flex items-center space-x-1 px-3 py-1.5 rounded-full text-xs font-semibold transition-all ${
            currentTheme === 'dark' 
              ? 'bg-slate-800 text-cyan-400 shadow-md' 
              : 'text-slate-500 hover:text-slate-900 dark:hover:text-white'
          }`}
        >
          <Moon size={14} />
          <span>Dark</span>
        </button>

      </div>
    </header>
  );
}