import { useState } from 'react'
import './App.css'

export default function App() {
  const [count, setCount] = useState(0)

  return (
    <div className="app">
      <h1>DolphoX Compiler</h1>
      <p>React + Vite is installed and working.</p>
      <button onClick={() => setCount((c) => c + 1)}>
        count is {count}
      </button>
    </div>
  )
}
