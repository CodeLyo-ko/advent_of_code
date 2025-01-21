#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    int a_x;
    int a_y;
    int b_x;
    int b_y;
    int res_x;
    int res_y;
    long long total = 0;
    double a;
    double b;

    double ratio;


    while(getchar() != EOF) {
        fseek(stdin, -1, SEEK_CUR);
        scanf("Button A: X+%d, Y+%d\nButton B: X+%d, Y+%d\nPrize: X=%d, Y=%d\n\n", &a_x, &a_y, &b_x, &b_y, &res_x, &res_y);
        ratio = a_y/(double)a_x;

        b = (10000000000000 + res_y - (ratio * (res_x + 10000000000000)))/(b_y - (ratio * b_x));

        a = (10000000000000 + res_x - (b * b_x)) / a_x;


        if (round(a) * a_x + round(b) * b_x == (10000000000000 + res_x) && round(a) * a_y + round(b) * b_y == (10000000000000 + res_y)  ) {
        total += a * 3 + b;
        }
    }
    printf("%lld\n", total);
    return 0;
}
