#include <stdio.h>
#include <stdlib.h>

int main() {
    char direction;
    int number;
    int dial = 50;
    int max_dial = 100;
    int res = 0;

    while (scanf("%c%d\n", &direction, &number) > 0) {
        switch (direction) {
            case 'L': 
                res -= dial == 0;
                dial -= number;
                while (dial < 0) {
                    res++;
                    dial += max_dial;
                }
                res += dial == 0;
                break;
            case 'R': 
                dial += number;
                res += dial == 0;
                while (dial > max_dial - 1) {
                    res++;
                    dial -= max_dial;
                }
                break;
        }
    } 
    printf("%d\n", res);
}
