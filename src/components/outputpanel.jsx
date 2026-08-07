import React, { useState } from 'react';

export default function OutputPanel({ outputData, isLoading }) {
  const [activeTab, setActiveTab] = useState('execution'); // 'execution', 'target', 'tac', 'ast', 'symbol'
  const [selectedLang, setSelectedLang] = useState('python'); // 'python', 'c', 'cpp', 'java'

  return (
    <div className="flex flex-col h-full overflow-hidden rounded-lg border border-[#333] bg-[#1e1e1e] text-[#d4d4d4] font-mono text-sm shadow-2xl">
      {/* Panel Header & Tabs */}
      <div className="flex flex-wrap items-center justify-between gap-2 border-b border-[#333] bg-[#252526] px-4 py-1 select-none">
        <div className="flex items-center space-x-2 overflow-x-auto">
          {/* Main Output Tabs */}
          <button
            onClick={() => setActiveTab('execution')}
            className={`px-3 py-1.5 border-b-2 text-xs font-semibold transition-colors flex items-center space-x-1 ${
              activeTab === 'execution'
                ? 'border-green-500 text-white bg-[#1e1e1e]'
                : 'border-transparent text-gray-400 hover:text-gray-200'
            }`}
          >
            <span className="text-green-400 font-bold">▶</span>
            <span>Execution Output</span>
          </button>
          
          <button
            onClick={() => setActiveTab('target')}
            className={`px-3 py-1.5 border-b-2 text-xs font-semibold transition-colors ${
              activeTab === 'target'
                ? 'border-blue-500 text-white bg-[#1e1e1e]'
                : 'border-transparent text-gray-400 hover:text-gray-200'
            }`}
          >
            Generated Target Code
          </button>
          <button
            onClick={() => setActiveTab('tac')}
            className={`px-3 py-1.5 border-b-2 text-xs font-semibold transition-colors ${
              activeTab === 'tac'
                ? 'border-blue-500 text-white bg-[#1e1e1e]'
                : 'border-transparent text-gray-400 hover:text-gray-200'
            }`}
          >
            TAC
          </button>
          <button
            onClick={() => setActiveTab('ast')}
            className={`px-3 py-1.5 border-b-2 text-xs font-semibold transition-colors ${
              activeTab === 'ast'
                ? 'border-blue-500 text-white bg-[#1e1e1e]'
                : 'border-transparent text-gray-400 hover:text-gray-200'
            }`}
          >
            AST
          </button>
          <button
            onClick={() => setActiveTab('symbol')}
            className={`px-3 py-1.5 border-b-2 text-xs font-semibold transition-colors ${
              activeTab === 'symbol'
                ? 'border-blue-500 text-white bg-[#1e1e1e]'
                : 'border-transparent text-gray-400 hover:text-gray-200'
            }`}
          >
            Symbol Table
          </button>
        </div>

        {/* Right side: Language Selector & Status */}
        <div className="flex items-center space-x-3">
          {activeTab === 'target' || activeTab === 'execution' ? (
            <select
              value={selectedLang}
              onChange={(e) => setSelectedLang(e.target.value)}
              className="bg-[#333] text-gray-200 text-xs px-2 py-1 rounded border border-[#444] focus:outline-none focus:border-blue-500"
            >
              <option value="python">Python (`output.py`)</option>
              <option value="c">C (`output.c`)</option>
              <option value="cpp">C++ (`output.cpp`)</option>
              <option value="java">Java (`Output.java`)</option>
            </select>
          ) : null}

          <div className="text-xs text-gray-400 flex items-center">
            {isLoading ? (
              <span className="flex items-center text-yellow-400">
                <span className="animate-spin h-2 w-2 border-2 border-yellow-400 border-t-transparent rounded-full mr-2"></span>
                Running...
              </span>
            ) : (
              <span className="flex items-center text-green-400">
                <span className="h-2 w-2 bg-green-400 rounded-full mr-1.5"></span>
                Ready
              </span>
            )}
          </div>
        </div>
      </div>

      {/* Panel Content Area */}
      <div className="flex-1 overflow-auto bg-[#1e1e1e] p-4">
        {isLoading ? (
          <div className="flex items-center justify-center h-full text-gray-500 animate-pulse">
            Executing program...
          </div>
        ) : (
          <pre className="whitespace-pre-wrap text-xs leading-relaxed text-white font-mono">
            {activeTab === 'execution' && (
              outputData?.executionResults?.[selectedLang] || 
              `$ Running output for [${selectedLang.toUpperCase()}].\n$ Output results will show here after execution...`
            )}
            {activeTab === 'target' && (
              outputData?.targetCodes?.[selectedLang] || 
              `// Target code for ${selectedLang.toUpperCase()} will appear here...`
            )}
            {activeTab === 'tac' && (outputData?.tacCode || '// Intermediate TAC code...')}
            {activeTab === 'ast' && (outputData?.astData || '// AST representation...')}
            {activeTab === 'symbol' && (outputData?.symbolTable || '// Symbol table contents...')}
          </pre>
        )}
      </div>
      
    </div>
  );
}