#include <stdio.h>
#include <stdlib.h>

int main() {
    char doorcode[5][5] = {{'\0', '\0', '1', '\0', '\0'}, {'\0', '2', '3', '4', '\0'}, {'5', '6', '7', '8', '9'}, {'\0', 'A', 'B', 'C', '\0'}, {'\0', '\0', 'D', '\0', '\0'}};

    // starting at 5
    int x = 0;
    int y = 2;

    char direction;
    while(getchar() != EOF) {
        fseek(stdin, -1, SEEK_CUR);
        while ((direction = getchar()) != '\n') {
            switch (direction) {
                case 'U':
                    y--;
                    if (y < 0 || doorcode[y][x] == '\0') y++;
                    break;
                case 'D':
                    y++;
                    if (y > 4 || doorcode[y][x] == '\0') y--;
                    break;
                case 'L':
                    x--;
                    if (x < 0 || doorcode[y][x] == '\0') x++;
                    break;
                case 'R':
                    x++;
                    if (x > 4 || doorcode[y][x] == '\0') x--;
                    break;
            }
        }
        printf("%c", doorcode[y][x]);
    }
     
        
    return 0;
}
