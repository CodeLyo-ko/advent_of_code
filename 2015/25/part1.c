#include <stdio.h>
#include <stdlib.h>

long long get_next_code(long long prev_code) {
    long long code = prev_code * 252533;
    code %= 33554393;
    return code;
}

int main() {
    int row = 2981;
    int column = 3075;

    long long code = 20151125;
    for (int i = 1; i <= column + row; i++) {
        for (int j = 1; j <= i; j++) {
            if (i - j + 1 == row && j == column) {
                printf("%d %d %lld\n",i - j + 1, j,  code);
            }
            
            code = get_next_code(code);
        }
    }
    return 0;
}
