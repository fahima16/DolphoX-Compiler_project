import React, { useEffect, useRef, useState } from 'react';
import { Terminal } from 'xterm';
import 'xterm/css/xterm.css';

export default function TerminalPanel({ runToken, language, code, setIsLoading, theme }) {
  const terminalRef = useRef(null);
  const socketRef = useRef(null);
  const termInstance = useRef(null);
  const [connected, setConnected] = useState(false);

  useEffect(() => {
    termInstance.current = new Terminal({ cursorBlink: true, cols: 80, rows: 24, theme: theme === 'dark' ? { background: '#060D1A', foreground: '#cdd6f4' } : undefined });
    termInstance.current.open(terminalRef.current);

    return () => {
      termInstance.current?.dispose();
    };
  }, [theme]);

  useEffect(() => {
    if (runToken === 0) return;
    if (!termInstance.current) return;

    setIsLoading(true);
    termInstance.current.clear();

    const socket = new WebSocket(`ws://${window.location.hostname}:5000/terminal`);
    socketRef.current = socket;

    socket.addEventListener('open', () => {
      setConnected(true);
      socket.send(JSON.stringify({ type: 'run', language, code }));
    });

    socket.addEventListener('message', (event) => {
      const data = JSON.parse(event.data);
      if (data.type === 'stdout' || data.type === 'stderr') {
        termInstance.current.write(data.payload.replace(/\n/g, '\r\n'));
      }
      if (data.type === 'prompt') {
        termInstance.current.write(data.payload.replace(/\n/g, '\r\n'));
      }
      if (data.type === 'done') {
        setIsLoading(false);
        termInstance.current.write('\r\n[Process complete]');
        socket.close();
      }
    });

    socket.addEventListener('close', () => {
      setConnected(false);
      setIsLoading(false);
    });

    socket.addEventListener('error', () => {
      setConnected(false);
      setIsLoading(false);
      termInstance.current.write('\r\n[Terminal connection failed]');
    });

    const dataListener = termInstance.current.onData((data) => {
      if (socket.readyState === WebSocket.OPEN) {
        socket.send(JSON.stringify({ type: 'stdin', payload: data }));
      }
    });

    return () => {
      dataListener.dispose();
      socket.close();
    };
  }, [runToken]);

  return (
    <div className="w-full rounded-lg border overflow-hidden shadow-2xl bg-[#060D1A] text-slate-200" style={{ minHeight: 140 }}>
      <div className="flex items-center justify-between px-4 py-2 border-b text-sm font-bold uppercase tracking-wider text-slate-300">
        <div>Build & Run: Output / Terminal</div>
        <div className="h-4 w-4 rotate-45 bg-slate-700/30 rounded-sm" />
      </div>
      <div className="h-32 md:h-32" ref={terminalRef} />
    </div>
  );
}
