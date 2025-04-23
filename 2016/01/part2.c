#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} pos_t;

int is_in_array(pos_t* array, int n, int x, int y) {

    for (int i = 0; i < n; i++) {
        if (array[i].x == x  && array[i].y == y) {
            return 1;
        }
    }
    return 0;
}

int main() {
    int x = 0;
    int y = 0;
    int prev_x = 0;
    int prev_y = 0;
    int direction = 0;
    char directions[4] = {'N', 'E', 'S', 'O'};

    pos_t* positions = malloc(400000 * sizeof(pos_t));
    int n_positions = 1;
    positions[0].x = 0;
    positions[0].y = 0;

    char rotation = ' ';
    int blocks = 0;
    int found = 0;
    while ((rotation = getchar()) != '\n') {
        prev_x = x;
        prev_y = y;
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
                for (int i = prev_y + 1; i <= y; i++) {
                    if (is_in_array(positions, n_positions, x, i)) {
                        found = 1;
                        y = i;
                        break;
                    }
                    positions[n_positions].x = x;
                    positions[n_positions].y = i;
                    n_positions++;
                }
                break;
            case 'E':
                x += blocks;
                for (int i = prev_x + 1; i <= x; i++) {
                    if (is_in_array(positions, n_positions, i, y)) {
                        found = 1;
                        x = i;
                        break;
                    }
                    positions[n_positions].x = i;
                    positions[n_positions].y = y;
                    n_positions++;
                }
                break;
            case 'S':
                y -= blocks;
                for (int i = y; i < prev_y; i++) {
                    if (is_in_array(positions, n_positions, x, i)) {
                        found = 1;
                        y = i;
                        break;
                    }
                    positions[n_positions].x = x;
                    positions[n_positions].y = i;
                    n_positions++;
                }
                break;
            case 'O':
                x -= blocks;
                for (int i = x; i < prev_x; i++) {
                    if (is_in_array(positions, n_positions, i, y)) {
                        found = 1;
                        x = i;
                        break;
                    }
                    positions[n_positions].x = i;
                    positions[n_positions].y = y;
                    n_positions++;
                }
                break;
        }

        
        if (found) {
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
