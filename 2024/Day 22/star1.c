#include <stdio.h>
#include <stdlib.h>

long long generate_random (long long in) {
    long long out = in;
    long long temp;

    temp = 64 * out;
    out ^= temp;
    out %= 16777216;

    temp = out / 32;
    out ^= temp;
    out %= 16777216;

    temp = 2048 * out;
    out ^= temp;
    out %= 16777216;

    return out;
}

int main() {
    long long number;

    long long total = 0;

    while (getchar() != EOF) {
        fseek(stdin, -1, SEEK_CUR);
        scanf("%lld\n", &number);

        for (int i = 0; i < 2000; i++) {
            number = generate_random(number);
        }
        printf("%lld\n", number);
        total += number;
    }

    printf("%lld\n", total);
    return 0;
}
