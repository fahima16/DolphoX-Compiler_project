const express = require('express');
const cors = require('cors');
const { spawn } = require('child_process');
const path = require('path');
const fs = require('fs');
const { WebSocketServer } = require('ws');

const app = express();
app.use(cors());
app.use(express.json());

const tempDir = path.join(__dirname, 'temp');

const deleteFileIfExists = (filePath) => {
  try {
    if (fs.existsSync(filePath)) {
      fs.unlinkSync(filePath);
    }
  } catch (error) {
    // ignore cleanup failures
  }
};

const cleanupTempDir = () => {
  try {
    if (fs.existsSync(tempDir)) {
      fs.rmSync(tempDir, { recursive: true, force: true });
    }
  } catch (error) {
    // ignore cleanup failures
  }
  fs.mkdirSync(tempDir, { recursive: true });
};

const getTempFilePath = (prefix, ext) => {
  const uniqueSuffix = Date.now().toString(36) + Math.random().toString(36).slice(2, 8);
  return path.join(tempDir, `${prefix}_${uniqueSuffix}${ext}`);
};

const normalizeScanfPrompt = (source) => {
  return source.replace(/scanf\(\s*"([^"]*?)%([^"]*)"\s*,/g, (match, prefix, suffix) => {
    const prompt = prefix;
    if (!prompt.trim()) {
      return match;
    }
    const escapedPrompt = prompt.replace(/\\/g, '\\\\').replace(/"/g, '\\"');
    return `printf("${escapedPrompt}"); scanf("%${suffix}",