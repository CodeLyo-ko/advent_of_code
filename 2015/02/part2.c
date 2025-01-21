#include <stdio.h>
#include <stdlib.h>

int main() {
    int s1, s2, s3;
    int total = 0;
    int min;

    while(getchar() != EOF) {
        fseek(stdin, -1, SEEK_CUR);
        scanf("%dx%dx%d\n", &s1, &s2, &s3);

        total += s1 * s2 * s3;

        min = s1 + s2;
        if (s1 + s3 < min) min = s1 + s3;
        if (s2 + s3 < min) min = s2 + s3;

        total += min * 2;
    }

    printf("%d\n", total);
}
