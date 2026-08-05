import java.util.Scanner;

public class test {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int x;
        x = 5;
        System.out.println(x);
        int y;
        y = 3;
        if (x > y) {
            System.out.println(x);
        }
        else {
            System.out.println(y);
        }
        int z;
        z = x + y;
        System.out.println(z);
        scanner.close();
    }
}
