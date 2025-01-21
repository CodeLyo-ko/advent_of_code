#include <stdio.h>
#include <stdlib.h>

int main() {
    int x = 101;
    int y = 103;

    long q1 = 0;
    long q2 = 0;
    long q3 = 0;
    long q4 = 0;

    long p_x, p_y, v_x, v_y;
    while(getchar() != EOF) {
        fseek(stdin, -1, SEEK_CUR);
        scanf("p=%ld,%ld v=%ld,%ld\n", &p_x, &p_y, &v_x, &v_y);
        p_x += 100 * v_x;
        p_y += 100 * v_y;
        while (p_x < 0)
            p_x += x;
        while(p_y < 0)
            p_y += y;
        p_x %= x;
        p_y %= y;

        printf("%ld %ld\n", p_x, p_y);

        if (p_x < x / 2) {
            if (p_y < y / 2) {
                q1++;
            }
            else if (p_y > y /2) {
                q3++;
            }
        }
        else if (p_x > x /2) {
            if (p_y < y / 2) {
                q2++;
            }
            else if (p_y > y /2) {
                q4++;
            }
        }
    }
    printf("%lld\n", q1 * q2 * q3 * q4);
    return 0;
}
