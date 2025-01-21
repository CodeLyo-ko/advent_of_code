#include <stdio.h>
#include <stdlib.h>

int main() {
    int a_x;
    int a_y;
    int b_x;
    int b_y;
    int res_x;
    int res_y;
    int total = 0;
    int min_token = 0;

    while(getchar() != EOF) {
        fseek(stdin, -1, SEEK_CUR);
        scanf("Button A: X+%d, Y+%d\nButton B: X+%d, Y+%d\nPrize: X=%d, Y=%d\n\n", &a_x, &a_y, &b_x, &b_y, &res_x, &res_y);

        min_token = 0;
        for (int i = 0; i <= 100; i++) {
            for (int j = 0; j <= 100; j++) {
                if (a_x * i + b_x * j == res_x && a_y * i + b_y * j == res_y) {
                    if (!min_token) min_token = i*3+j;
                    min_token = ((i * 3 + j)<min_token)?min_token:(i*3+j);
                }
            }
        }
        total += min_token;
    }
    printf("%d\n", total);
    return 0;
}
