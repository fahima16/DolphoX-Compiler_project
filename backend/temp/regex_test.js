const code = 'public class Main { public static void main(String[] args) { System.out.println("hi"); } }';
const match = code.match(/public\s+class\s+([A-Za-z_][A-Za-z0-9_]*)/);
console.log('code:', code);
console.log('match:', match);
