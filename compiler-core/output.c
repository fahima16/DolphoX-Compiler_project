#include <stdio.h>

int main() {
    int x;
    x = 5;
    printf("%d\n", x);
    int y;
    y = 3;
    if (x > y) {
        printf("%d\n", x);
    }
    else {
        printf("%d\n", y);
    }
    int z;
    z = x + y;
    printf("%d\n", z);
    return 0;
}
