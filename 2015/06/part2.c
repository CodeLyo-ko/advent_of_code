#include <stdio.h>
#include <stdlib.h>
#define size_max 1000

typedef enum {
    ON,
    OFF,
    TOGGLE
} action_t;

void split_input(char* line, action_t* action, int* x_start, int* x_end, int* y_start, int* y_end) {
    if (line[1] == 'o') {
        *action = TOGGLE;
    }
    else if (line[6] == 'n') {
        *action = ON;
    }
    else {
        *action = OFF;
    }

    sscanf(line, "%*[^0-9] %d,%d through %d,%d\n", x_start, y_start, x_end, y_end);
}

int main() {
    int** lights = malloc(size_max * size_max * sizeof(int));
    for (int i = 0; i < size_max; i++) {
        lights[i] = malloc(size_max * sizeof(int));
        for (int j = 0; j < size_max; j++) {
            lights[i][j] = 0;
        }
    }

    char* line = malloc(100 * sizeof(char));
    action_t action ;
    int x_start, y_start;
    int x_end, y_end;

    while(getchar() != EOF) {
        fseek(stdin, -1, SEEK_CUR);
        fgets(line, 100, stdin);
        split_input(line, &action, &x_start, &x_end, &y_start, &y_end);

        for (int i = x_start; i <= x_end; i++) {
            for (int j = y_start; j <= y_end; j++) {
                switch (action) {
                    case ON:
                        lights[i][j]++;
                        break;
                    case OFF:
                        lights[i][j]--;
                        if (lights[i][j] < 0) lights[i][j] = 0;
                        break;
                    case TOGGLE:
                        lights[i][j] += 2;
                        break;
                }
            }
        }
    }

    int total = 0;

    for (int i = 0; i < size_max; i++) {
        for (int j = 0; j < size_max; j++) {
            total += lights[i][j];
        }
    }

    printf("%d\n", total);
}
