#include <stdio.h>
#include <stdlib.h>

int main() {
    int x = 0;
    int y = 0;
    int direction = 0;
    char directions[4] = {'N', 'E', 'S', 'O'};

    char rotation = ' ';
    int blocks = 0;
    while ((rotation = getchar()) != '\n') {
        switch (rotation) {
            case 'L':
                direction--;
                if (direction < 0) direction = 3;
                break;
            case 'R':
                direction++;
                if (direction > 3) direction = 0;
                break;
        }
        scanf("%d", &blocks);
        switch (directions[direction]) {
            case 'N':
                y += blocks;
                break;
            case 'E':
                x += blocks;
                break;
            case 'S':
                y -= blocks;
                break;
            case 'O':
                x -= blocks;
                break;
        }

        if (getchar() != ',') {
            break;
        }
        getchar();
    }
    printf("%d\n", abs(x) + abs(y));
    return 0;
}
