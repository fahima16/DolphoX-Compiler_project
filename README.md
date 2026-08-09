# DolphoX-Compiler_project

## Project Overview

This repository contains the DolphoX compiler project. It includes:
- a frontend web UI built with Vite and React,
- a backend Node.js server with WebSocket/terminal support,
- a compiler core implemented in C with lexer, parser, semantic analysis, intermediate code generation, optimizer, and code generation modules.

## What we completed so far

1. Set up the frontend application using Vite and React.
2. Integrated editor and terminal components for interactive code editing and output display.
3. Created the backend server in `backend/` with WebSocket support using `express`, `ws`, and `node-pty`.
4. Implemented compiler-core sources in `compiler-core/` with modular components for lexing, parsing, semantic analysis, intermediate representation, optimization, and code generation.
5. Added scripts and support files for running the frontend and backend.
6. Organized the repository structure to separate frontend, backend, and compiler core logic.

## Project structure

- `backend/` - Node.js server code and backend dependencies.
- `compiler-core/` - Compiler implementation in C, including lexer, parser, semantic analysis, optimizer, and code generation.
- `src/` - Frontend React application source files.
- `vite.config.js` - Vite configuration for the frontend.
- `package.json` - Frontend project configuration and scripts.
- `backend/package.json` - Backend project configuration and scripts.

## How to start the project

### 1. Install dependencies

From the repository root:

```bash
npm install
```

Then install backend dependencies:

```bash
cd backend
npm install
```

### 2. Start the backend server

From the `backend/` directory:

```bash
npm run start
```

If you want automatic restarts during development, use:

```bash
npm run dev
```

### 3. Start the frontend

From the repository root:

```bash
npm run dev
```

### 4. Open the app

Use the local URL shown by Vite (usually `http://localhost:5173`) to open the frontend app in your browser.

## Development process step by step

1. Set up the root Vite + React app and verify the UI build.
2. Add editor and terminal panels to the frontend for code entry and runtime output.
3. Build the backend WebSocket server to connect the frontend terminal and execute commands.
4. Create the compiler core modules under `compiler-core/` to handle source analysis and code generation.
5. Connect frontend actions to backend services for compilation and execution.
6. Test the application flow and ensure the frontend and backend start correctly.

## Notes

- Do not change project logic in this README update.
- Backend and frontend are started separately.
- The compiler core is located in `compiler-core/` and can be extended with additional language support or codegen features.

