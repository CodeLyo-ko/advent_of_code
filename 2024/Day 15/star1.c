#include <stdio.h>
#include <stdlib.h>

int main() {
    char** map = malloc(100 * 100 * sizeof(char));
    int n = 0;
    char* input = malloc(30000 * sizeof(char));
    int n_input = 0;

    while(getchar() != '\n') {
        fseek(stdin, -1, SEEK_CUR);
        map[n] = malloc(100 * sizeof(char));
        fgets(map[n], 100, stdin);
        n++;
    }

    while(getchar() != EOF) {
        fseek(stdin, -1, SEEK_CUR);
        input[n_input] = getchar();
        if (input[n_input] != '\n') n_input++;
    }

    int x,y;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (map[i][j] == '@') {
                x = i;
                y = j;
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
                    case 'O':
                        j = x - 1;
                        while (map[j][y] == 'O') {
                            j--;
                        }
                        if (map[j][y] == '.') {
                            map[j][y] = 'O';
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
                    case 'O':
                        j = x + 1;
                        while (map[j][y] == 'O') {
                            j++;
                        }
                        if (map[j][y] == '.') {
                            map[j][y] = 'O';
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
                    case 'O':
                        j = y + 1;
                        while (map[x][j] == 'O') {
                            j++;
                        }
                        if (map[x][j] == '.') {
                            map[x][j] = 'O';
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
                    case 'O':
                        j = y - 1;
                        while (map[x][j] == 'O') {
                            j--;
                        }
                        if (map[x][j] == '.') {
                            map[x][j] = 'O';
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
        for (int j = 0; j < n; j++) {

            if (map[i][j] == 'O')
                total += 100 * i + j;
        }
    }

    printf("%d\n", total);
    return 0;
}
