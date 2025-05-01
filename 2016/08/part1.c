#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define HEIGHT 6
#define WIDTH 50 

void exec_command(int** screen, char* line) {
    char rect[] = "rect";
    int len_rect = strlen(rect);
    char rotate_row[] = "rotate row";
    int len_rotate_row = strlen(rotate_row);
    char rotate_column[] = "rotate column";
    int len_rotate_column = strlen(rotate_column);

    if ( !strncmp(line, rect, len_rect)) {
        int width, height;
        char* endptr;
        width = strtol(&line[len_rect + 1], &endptr, 10);
        height = strtol(&endptr[1], NULL, 10);
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                screen[i][j] = 1;
            }
        }
    }
    else if (!strncmp(line, rotate_row, len_rotate_row)) {
        int row, n_pixel;
        char* endptr;
        row = strtol(&line[len_rotate_row + 3], &endptr, 10);
        n_pixel = strtol(&endptr[4], NULL, 10);
        for (int k = 0; k < n_pixel; k++) {
            int temp = screen[row][WIDTH - 1];
            for (int j = WIDTH - 1; j > 0; j--) {
                screen[row][j] = screen[row][j - 1];
            }
            screen[row][0] = temp;
        }
    }
    else {
        int column, n_pixel;
        char* endptr;
        column = strtol(&line[len_rotate_column + 3], &endptr, 10);
        n_pixel = strtol(&endptr[4], NULL, 10);
        for (int k = 0; k < n_pixel; k++) {
            int temp = screen[HEIGHT - 1][column];
            for (int i = HEIGHT - 1; i > 0; i--) {
                screen[i][column] = screen[i - 1][column];
            }
            screen[0][column] = temp;
        }
    }
}


int nb_pixels(int** screen) {
    int total = 0;
    for ( int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            total += screen[i][j];
        }
    }
    return total;
}


int main() {
    int** screen = malloc(HEIGHT * sizeof(int*));
    for (int i = 0; i < HEIGHT; i++) {
        screen[i] = calloc(WIDTH,  sizeof(int));
    }

    char* line = malloc(100 * sizeof(char));
    while(fgets(line, 100, stdin)){
        exec_command(screen, line);
    }

    printf("%d\n", nb_pixels(screen));
    return 0;
}
