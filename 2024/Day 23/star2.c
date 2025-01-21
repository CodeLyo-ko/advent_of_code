#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int in_links(int** links, int a, int b) {
    for (int i = 1; i <= links[a][0]; i++) {
        if (links[a][i] == b) return 1;
    }
    return 0;
}

void print_tab(int* t, int n) {
    for (int i = 0; i < n; i++) {
        printf("%c%c,", t[i]/26 + 'a', t[i]%26 + 'a');
    }
    printf("\n");
}

int check_clique(int** links, int* clique, int n_clique) {
    for (int i = 1;  i < n_clique; i++) {
        for (int j = 1; j < i; j++) {
            if (!in_links(links, clique[i], clique[j])) {
                return 0;
            }
        }
    }

    return 1;
}

void copy(int* t1, int n, int* t2) {
    for (int i = 0; i < n; i++) {
        t2[i] = t1[i];
    }
}

int n_bits(int n) {
    int res = 0;
    while (n != 0) {
        res += n%2;
        n/=2;
    }
    return res;
}

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

    int* clique = malloc(26 * 26 * sizeof(int));
    int n_clique = 0;

    int* clique_max = malloc(26 * 26 * sizeof(int));
    int n_max = 0;
    int subgroup_temp;
    int current;
    for (int i = 0; i < 26 * 26; i++) {
        n_clique = 1;
        clique[0] = i;
        for (int subgroup = pow(2, links[i][0]) - 1; subgroup > 0; subgroup--) {
            n_clique = 1;
            subgroup_temp = subgroup;
            for (int j = 1; j <= links[i][0]; j++) {
                current = subgroup_temp%2;
                subgroup_temp/=2;
                if (current) {
                    if (links[i][j] < i) break;

                    clique[n_clique++] = links[i][j];
                }
            }

            if (check_clique(links, clique, n_clique)) {
                if (n_clique > n_max) {
                    copy(clique, n_clique, clique_max);
                    n_max = n_clique;
                }
            }
        }
    }

    print_tab(clique_max, n_max);
    printf("%d\n", n_max);
    return 0;
}
