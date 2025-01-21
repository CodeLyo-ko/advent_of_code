#include <stdio.h>
#include <stdlib.h>

int main() {
    int** links = malloc(26 * 26 * 26 * 27 * sizeof(int));
    for (int i = 0; i < 26 * 26; i++) {
        links[i] = malloc(26 * 27 * sizeof(int));
        links[i][0] = 0;
    }

    char c11, c12, c21, c22;
    int c1, c2;

    while(getchar() != EOF) {
        fseek(stdin, -1, SEEK_CUR);
        scanf("%c%c-%c%c\n", &c11, &c12, &c21, &c22);
        c1 = (c11 - 'a') * 26 + c12 - 'a';
        c2 = (c21 - 'a') * 26 + c22 - 'a';
        links[c1][++links[c1][0]] = c2;
        links[c2][++links[c2][0]] = c1;
    }

    int c3;
    int total = 0;
    for (int i = 0; i < 26 * 26; i++) {
        c1 = i;
        for (int j = 1; j < links[c1][0]; j++) {
            c2 = links[c1][j];
            if (c2 < c1) continue;

            for (int k = j; k <= links[c1][0]; k++) {
                c3 = links[c1][k];
                if (c3 < c1) continue;

                for (int l = 1; l <= links[c2][0]; l++) {
                    if (links[c2][l] == c3) {
                        if (c1/26 + 'a' == 't' || c2/26 + 'a' == 't' || c3/26 + 'a' == 't') {
                            total++;
                        printf("%c%c, %c%c, %c%c\n", c1/26 + 'a', c1%26 + 'a', c2/26 + 'a', c2%26 + 'a', c3/26 + 'a', c3%26 + 'a');
                        }
                    }
                }
            }
        }
    }

    printf("%d\n", total);
    return 0;
}
