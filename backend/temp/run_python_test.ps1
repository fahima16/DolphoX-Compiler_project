const fs = require('fs');
const path = require('path');
const filePath = path.join(process.cwd(), 'temp', 'test_api_and_ws.js');
const content = `const fetch = globalThis.fetch;
const WebSocket = require('ws');
(async () => {
  try {
    console.log('POST compile...');
    const response = await fetch('http://127.0.0.1:5000/api/compile', {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify({ code: 'x = "hi"\nprint(x)\n', language: 'python', input: '' }),
    });
    console.log('compile', await response.text());
  } catch (err) {
    console.error('compile error', err);
  }
  try {
    console.log('WS test...');
    const ws = new WebSocket('ws://127.0.0.1:5000/terminal');
    ws.on('open', () => {
      console.log('WS open');
      ws.send(JSON.stringify({ type: 'run', language: 'python', code: 'x = "hi"\nprint(x)\n' }));
    });
    ws.on('message', (message) => {
      const data = JSON.parse(message.toString());
      console.log('WS msg', data);
      if (data.type === 'done') {
        ws.close();
      }
    });
    ws.on('error', (err) => console.error('WS error', err.message));
    ws.on('close', () => console.log('WS closed'));
  } catch (err) {
    console.error('WS creation error', err);
  }
})();`;
fs.writeFileSync(filePath, content, 'utf8');
node filePath;
