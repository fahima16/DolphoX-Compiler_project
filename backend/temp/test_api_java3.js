const fetch = globalThis.fetch;
(async () => {
  try {
    const response = await fetch('http://127.0.0.1:5000/api/compile', {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify({ code: 'public class Main { public static void main(String[] args) { System.out.println("hi"); } }', language: 'java', input: '' }),
    });
    console.log('RESPONSE', await response.text());
  } catch (err) {
    console.error('ERROR', err);
  }
})();
