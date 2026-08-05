const http = require('http');
const code = `#include <stdio.h>
int main(){
    int x;
    scanf("%d", &x);
    printf("%d\\n", x);
    return 0;
}`;
const payload = JSON.stringify({ code, language: 'c', input: '7\n' });
const req = http.request({ host: '127.0.0.1', port: 5000, path: '/api/compile', method: 'POST', headers: { 'Content-Type': 'application/json' } }, res => {
  let data = '';
  res.on('data', c => data += c);
  res.on('end', () => console.log(data));
});
req.on('error', err => { console.error(err.message); process.exit(1); });
req.write(payload);
req.end();
