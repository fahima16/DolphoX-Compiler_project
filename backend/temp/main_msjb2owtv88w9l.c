#include <stdio.h>

#include <iostream>
using namespace std;

int findMax(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max)
            max = arr[i];
    }
    return max;
}

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;
    int arr[n];
    for (int i = 0; i < n; i++) {
        cout << "Enter element " << i + 1 << ": ";
        cin >> arr[i];
    }
    int max = findMax(arr, n);
    if (max % 2 == 0)
        cout << "Max is " << max << " (Even)" << endl;
    else
        cout << "Max is " << max << " (Odd)" << endl;
    return 0;
}