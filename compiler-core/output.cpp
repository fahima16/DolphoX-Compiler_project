#include <iostream>
using namespace std;

int main() {
    int add(int a, int b) {
{
    if (a > b) {
    return a;
    }
    return b;
    }
    }
    int x;
    x = add(5, 3);
    cout << x << endl;
    int i;
    i = 0;
    while (i < 3) {
    cout << i << endl;
    i = i + 1;
    }
    return 0;
}
