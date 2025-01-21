#include <stdio.h>
#include <stdlib.h>

void copy_map(char** map, int n, char** out) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n * 2; j++) {
            out[i][j] = map[i][j];
        }
    }
}

int push_box(char** map, int x, int y, char dir) {
    switch (dir) {
        case '<':
            if (map[x][y - 1] == ']') {
                push_box(map, x, y - 2, dir);
            }

            if (map[x][y - 1] == '.') {
                map[x][y - 1] = '[';
                map[x][y] = ']';
                map[x][y + 1] = '.';
            }
            break;
        case '^':
            if (map[x - 1][y] == '#' || map[x - 1][y + 1] == '#') break;
            if (map[x - 1][y] == '[') {
                push_box(map, x - 1, y, dir);
            }
            else if (map[x - 1][y + 1] == '[') {
                push_box(map, x - 1, y + 1, dir);
            }
            if (map[x - 1][y - 1] == '[') {
                push_box(map, x - 1, y - 1, dir);
            }

            if (map[x - 1][y] == '.' && map[x - 1][y + 1] == '.') {
                map[x - 1][y] = '[';
                map[x - 1][y + 1] = ']';
                map[x][y] = '.';
                map[x][y + 1] = '.';
            }
            break;
        case '>':
            if (map[x][y + 2] == '[') {
                push_box(map, x, y + 2, dir);
            }

            if (map[x][y + 2] == '.') {
                map[x][y + 1] = '[';
                map[x][y + 2] = ']';
                map[x][y] = '.';
            }
            break;
        case 'v':
            if (map[x + 1][y] == '#' || map[x + 1][y + 1] == '#') break;
            if (map[x + 1][y] == '[') {
                push_box(map, x + 1, y, dir);
            }
            else if (map[x + 1][y + 1] == '[') {
                push_box(map, x + 1, y + 1, dir);
            }
            if (map[x + 1][y - 1] == '[') {
                push_box(map, x + 1, y - 1, dir);
            }

            if (map[x + 1][y] == '.' && map[x + 1][y + 1] == '.') {
                map[x + 1][y] = '[';
                map[x + 1][y + 1] = ']';
                map[x][y] = '.';
                map[x][y + 1] = '.';
            }
            break;
    }
    return map[x][y] != '[';

}

int main() {
    char** map_v1 = malloc(100 * 100 * sizeof(char));
    int n = 0;
    char* input = malloc(30000 * sizeof(char));
    int n_input = 0;

    while(getchar() != '\n') {
        fseek(stdin, -1, SEEK_CUR);
        map_v1[n] = malloc(100 * sizeof(char));
        fgets(map_v1[n], 100, stdin);
        n++;
    }

    while(getchar() != EOF) {
        fseek(stdin, -1, SEEK_CUR);
        input[n_input] = getchar();
        if (input[n_input] != '\n') n_input++;
    }

    char** map = malloc(200 * 100 * sizeof(char));
    char** map_temp = malloc(200 * 100 * sizeof(char));


    int x,y;

    for (int i = 0; i < n; i++) {
        map[i] = malloc(200 * sizeof(char));
        map_temp[i] = malloc(200 * sizeof(char));
        for (int j = 0; j < n; j++) {
            switch (map_v1[i][j]) {
                case '#' :
                    map[i][j * 2] = '#';
                    map[i][j * 2 + 1] = '#';
                    break;
                case 'O':
                    map[i][j * 2] = '[';
                    map[i][j * 2 + 1] = ']';
                    break;
                case '@':
                    x = i;
                    y = j * 2;
                    map[i][j * 2] = '@';
                    map[i][j * 2 + 1] = '.';
                    break;
                case '.':
                    map[i][j * 2] = '.';
                    map[i][j * 2 + 1] = '.';
                    break;
            }
        }
    }

    int j;

    for (int i = 0; i < n_input; i++) {
        switch (input[i]) {
            case '^':
                switch(map[x - 1][y]) {
                    case '#': break;
                    case '.':
                        map[x - 1][y] = '@';
                        map[x][y] = '.';
                        x--;
                        break;
                    case ']':
                        copy_map(map, n, map_temp);
                        if (push_box(map_temp, x - 1, y - 1, input[i])) {
                            copy_map(map_temp, n, map);
                        }

                        if (map[x - 1][y] == '.') {
                            map[x - 1][y] = '@';
                            map[x][y] = '.';
                            x--;
                        }
                        break;
                    case '[':
                        copy_map(map, n, map_temp);
                        if (push_box(map_temp, x - 1, y, input[i])) {
                            copy_map(map_temp, n, map);
                        }

                        if (map[x - 1][y] == '.') {
                            map[x - 1][y] = '@';
                            map[x][y] = '.';
                            x--;
                        }
                        break;
                }
                break;
            case 'v':
                switch(map[x + 1][y]) {
                    case '#': break;
                    case '.':
                        map[x + 1][y] = '@';
                        map[x][y] = '.';
                        x++;
                        break;
                    case ']':
                        copy_map(map, n, map_temp);
                        if (push_box(map_temp, x + 1, y - 1, input[i])) {
                            copy_map(map_temp, n, map);
                        }
                        if (map[x + 1][y] == '.') {
                            map[x + 1][y] = '@';
                            map[x][y] = '.';
                            x++;
                        }
                        break;
                    case '[':
                        copy_map(map, n, map_temp);
                        if (push_box(map_temp, x + 1, y, input[i])) {
                            copy_map(map_temp, n, map);
                        }
                        if (map[x + 1][y] == '.') {
                            map[x + 1][y] = '@';
                            map[x][y] = '.';
                            x++;
                        }
                        break;
                }
                break;
            case '>':
                switch(map[x][y + 1]) {
                    case '#': break;
                    case '.':
                        map[x][y + 1] = '@';
                        map[x][y] = '.';
                        y++;
                        break;
                    case '[':
                        copy_map(map, n, map_temp);
                        if (push_box(map_temp, x, y + 1, input[i])) {
                            copy_map(map_temp, n, map);
                        }
                        if (map[x][y + 1] == '.') {
                            map[x][y + 1] = '@';
                            map[x][y] = '.';
                            y++;
                        }
                        break;
                }
                break;
            case '<':
                switch(map[x][y - 1]) {
                    case '#': break;
                    case '.':
                        map[x][y - 1] = '@';
                        map[x][y] = '.';
                        y--;
                        break;
                    case ']':
                        copy_map(map, n, map_temp);
                        if (push_box(map_temp, x, y - 2, input[i])) {
                            copy_map(map_temp, n, map);
                        }
                        if (map[x][y - 1] == '.') {
                            map[x][y - 1] = '@';
                            map[x][y] = '.';
                            y--;
                        }
                        break;
                }
                break;
        }
    }

    int total = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n * 2; j++) {
            printf("%c", map[i][j]);
            if (map[i][j] == '[') {
                total += 100 * i + j;
            }
        }
        printf("\n");
    }

    printf("%d\n", total);
    return 0;
}
