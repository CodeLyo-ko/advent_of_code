#include <stdio.h>
#include <stdlib.h>

int main() {
    int doorcode[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

    // starting at 5
    int x = 1;
    int y = 1;

    char direction;
    while(getchar() != EOF) {
        fseek(stdin, -1, SEEK_CUR);
        while ((direction = getchar()) != '\n') {
            switch (direction) {
                case 'U':
                    y--;
                    if (y < 0) y = 0;
                    break;
                case 'D':
                    y++;
                    if (y > 2) y = 2;
                    break;
                case 'L':
                    x--;
                    if (x < 0) x = 0;
                    break;
                case 'R':
                    x++;
                    if (x > 2) x = 2;
                    break;
            }
        }
        printf("%d", doorcode[y][x]);
    }
     
        
    return 0;
}
