#include <stdio.h>
#include <stdlib.h>
#define MAX_ 10

int is_possible(int n, int m, int n_pres) {
    return n * m >= n_pres * 3 * 3;
}

int main() {
    size_t dump = MAX_;
    char* dump_line = malloc(MAX_ * sizeof(char));
    for (int i = 0; i < 30; i++) {
        getline(&dump_line, &dump, stdin);
    }

    int n, m, n_pres, temp;
    int res = 0;
    while(getchar() != EOF) {
        fseek(stdin, -1, SEEK_CUR);
        n_pres = 0;
        scanf("%dx%d: ", &n, &m);
        for (int i = 0; i < 6; i++) {
            scanf("%d", &temp);
            n_pres += temp;
        }
        getchar();
        res += is_possible(n, m, n_pres);
    }
    printf("%d\n", res);
    return 0;
}

