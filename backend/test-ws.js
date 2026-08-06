const WebSocket = require("ws");
const ws = new WebSocket("ws://127.0.0.1:5000/terminal");
ws.on("open", () => {
  console.log("OPEN");
  ws.send(JSON.stringify({ type: "run", language: "c", code: "#include <stdio.h>\nint main(){ int x; scanf(\"%d\", &x); printf(\"%d\\n\", x+1); return 0; }" }));
  setTimeout(() => ws.send(JSON.stringify({ type: "stdin", payload: "5\r" })), 500);
});
ws.on("message", (m) => console.log("MSG", m.toString()));
ws.on("close", () => console.log("CLOSED"));
ws.on("error", (err) => console.error("ERR", err));
setTimeout(() => {}, 5000);
