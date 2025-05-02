#include <stdio.h>
#include <stdlib.h>

int main() {
    char c;
    int length = 0; 
    while ((c = getchar()) != '\n') {
        if (c != '(') {
            length++;
            continue;
        }
        int a, b;
        scanf("%dx%d)", &a, &b);
        length += a*b;
        for (int i = 0; i < a; i++) getchar();
    }
    printf("%d\n", length);
    return 0;
}
