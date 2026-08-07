#include <stdio.h>

import java.util.Scanner;

public class MaxFinder {
    static int findMax(int[] arr) {
        int max = arr[0];
        for (int i = 1; i < arr.length; i++) {
            if (arr[i] > max)
                max = arr[i];
        }
        return max;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter number of elements: ");
        int n = sc.nextInt();
        int[] arr = new int[n];
        for (int i = 0; i < n; i++) {
            System.out.print("Enter element " + (i + 1) + ": ");
            arr[i] = sc.nextInt();
        }
        int max = findMax(arr);
        if (max % 2 == 0)
            System.out.println("Max is " + max + " (Even)");
        else
            System.out.println("Max is " + max + " (Odd)");
    }
}