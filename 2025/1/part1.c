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
                dial -= number;
                while (dial < 0) {
                    dial += max_dial;
                }
                break;
            case 'R': 
                dial += number;
                while (dial > max_dial - 1) {
                    dial -= max_dial;
                }
                break;
        }
        res += dial == 0;
    }
    
    printf("%d\n", res);
}
