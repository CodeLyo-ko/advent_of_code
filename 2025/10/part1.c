#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_ 2000

typedef struct {
    int* light;
    int n_light;
    int** button;
    int n_button;
    int* joltage;
    int n_joltage;
} machine;

void combinations(int k, int l, int* res, int* n, int curr, int n_curr) {
    if (n_curr == k) {
        res[(*n)++] = curr;
        return;
    }
    int last_curr;
    for (int i = l; i > 0; i--) {
        last_curr = curr;
        curr += pow(2, i - 1);
        n_curr++;
        combinations(k, i - 1, res, n, curr, n_curr);
        curr = last_curr; 
        n_curr--;
    }
}


int min_button(machine m) {
    int* comb = malloc(MAX_ * sizeof(int));
    int n;
    int* button;

    int k;
    for (int i = 1; i <= m.n_light; i++) {
        n = 0;
        combinations(i, m.n_button, comb, &n, 0, 0);
        for (int j = 0; j < n; j++) {
            button = calloc(m.n_light, sizeof(int));
            k = 0;
            while (comb[j] != 0) {
                if (comb[j]%2 == 1) {
                    for (int l = 0; l < m.n_light; l++) {
                        if (m.button[k][l]) {
                            button[l]++;
                            button[l]%=2;
                        }
                    }
                }
                comb[j] /= 2;
                k++;
            }

            for (int l = 0; l < m.n_light; l++) {
                if (button[l] != m.light[l]) {
                    break;
                }
                if (l == m.n_light - 1){
                    free(button);
                    return i;}
            }
            free(button);
        }
    }
}

int main() {
    machine* m = malloc(MAX_ * sizeof(machine));
    int n = 0;

    char c;
    int b;
    while(getchar() != EOF) {
        m[n].light = malloc(MAX_ * sizeof(int));
        m[n].n_light = 0;
        while((c = getchar()) != ']') {
            m[n].light[m[n].n_light++] = c == '#' ? 1 : 0;
        }
        m[n].button = malloc(m[n].n_light * MAX_ * sizeof(int));
        m[n].n_button = 0;
        getchar();
        while(getchar() != '{') {
            m[n].button[m[n].n_button] = calloc(m[n].n_light, sizeof(int));
            while(getchar() != ' ') {
                fseek(stdin, -1, SEEK_CUR);
                scanf("%d%c", &b, &c);
                m[n].button[m[n].n_button][b] = 1;
            }
            m[n].n_button++;
        }

        m[n].joltage = malloc(MAX_ * sizeof(int));
        m[n].n_joltage = 0;
        while(getchar() != '\n') {
            fseek(stdin, -1, SEEK_CUR);
            scanf("%d%c", &b, &c);
            m[n].joltage[m[n].n_joltage++] = b;
        }
        n++;
    }

    int res;
    for (int i = 0; i < n; i++) {
        res += min_button(m[i]);
    }
    printf("%d\n", res);
    return 0;
}
