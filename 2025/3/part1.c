#include <stdio.h>
#include <stdlib.h>

int main(){
    int number;
    int max1 = 0;
    int prev_max1, prev_max2;
    int max2 = 0;
    int res = 0;
    while((number = getchar()) != EOF) {
        max1 = 0;
        max2 = 0;
        fseek(stdin, -1, SEEK_CUR);
        while((number = getchar()) != '\n') {
            number -= '0';
            if (number > max1) {
                prev_max1 = max1;
                prev_max2 = number;
                max1 = number;
                max2 = 0;
            }
            else if (number > max2) {
                max2 = number;
            }
        }
        if (max2 == 0) {
            max1 = prev_max1;
            max2 = prev_max2;
        }

        res += max1 * 10 + max2;
    }

    printf("%d\n", res);

    return 0;
}
