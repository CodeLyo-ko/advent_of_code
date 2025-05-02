#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 500000

int len_int(int a) {
    char str[10];
    sprintf(str, "%d", a);
    return strlen(str);
}

long long decompress(int n) {
    long long length = 0; 
    char c;
    int i = 0;
    while (i < n && (c = getchar()) != EOF ) {
        i++;
        if (c ==  '\n')
            return length;
        if (c != '(') {
            length++;
            continue;
        }
        int a, b;
        scanf("%dx%d)", &a, &b);
        i += 2 + len_int(a) + len_int(b) + a;
        length += b * decompress(a);
    }
    return length;
}

int main() {
    long long length = decompress(MAX_LENGTH);
    printf("%lld\n", length);
    return 0;
}
