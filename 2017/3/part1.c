#include <stdio.h>
#include <stdlib.h>

char next_move(char move) {
    switch(move) {
        case 'l':
            return 'd';
        case 'r':
            return 'u';
        case 'u':
            return 'l';
        case 'd':
            return 'r';
    }
}

int main() {
    int input = 325489;

    int x = 0;
    int y = 0;
    char move = 'r';
    int max_move = 1;
    int curr_move = 0;
    int changed_dir = 0;

    for (int i = 2; i <= input; i++) {
        switch (move) {
            case 'l': 
                x--;
                break;
            case 'r':
                x++;
                break;
            case 'u':
                y--;
                break;
            case 'd':
                y++;
                break;
        }
        curr_move++;
        if (curr_move == max_move) {
            changed_dir++;
            if (changed_dir == 2) {
                changed_dir = 0;
                max_move++;
            }
            curr_move = 0;
            move = next_move(move);
        }
    }

    if (x < 0) x = -x;
    if (y < 0) y = -y;
    printf("%d\n", x + y); 



    return 0;
}
