#include <stdio.h>

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
    printf("%d\n", x);
    int i;
    i = 0;
    while (i < 3) {
    printf("%d\n", i);
    i = i + 1;
    }
    return 0;
}
