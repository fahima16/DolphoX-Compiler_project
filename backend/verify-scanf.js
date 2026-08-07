const { normalizeScanfPrompt } = require('./scanf-normalizer');

const samples = [
  'int main(){ int x; scanf("%d", &x); printf("%d", x); return 0; }',
  'int main(){ int x; scanf("Enter value: %d", &x); printf("%d", x); return 0; }',
];

for (const sample of samples) {
  console.log(normalizeScanfPrompt(sample));
  console.log('---');
}
