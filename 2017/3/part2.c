#include <stdio.h>
#include <stdlib.h>
#define MAX_ 1000

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
    int** grid = malloc(MAX_ * MAX_ * sizeof(int));
    for (int i = 0; i < MAX_; i++) {
        grid[i] = calloc(MAX_, sizeof(int));
    }

    int x = MAX_ / 2;
    int y = x;
    grid[x][y] = 1;
    char move = 'r';
    int max_move = 1;
    int curr_move = 0;
    int changed_dir = 0;
    int val;

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

        val = grid[x-1][y] + grid[x-1][y-1] + grid[x-1][y+1] + grid[x][y-1] + grid[x][y+1] + grid[x+1][y-1] + grid[x+1][y] + grid[x+1][y+1];
        grid[x][y] = val;
        if (val > input)  {
            printf("%d\n", val);
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

    return 0;
}
