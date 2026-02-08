#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_ 2000
#define MAX_INT 2000

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


int min_button(machine m, int* joltage) {
    int zero = 1;
    int pair = 1;
    for (int i = 0; i < m.n_joltage; i++){
        if (joltage[i] != 0) {
            zero = 0;
        }
        if (joltage[i]%2 == 1) {
            pair = 0;
        }
    }
    if (zero){
        return 0;
    }

    int* comb = malloc(MAX_ * sizeof(int));
    int n;
    int* button;
    int mini = MAX_INT;
    int temp;

    if (pair) {
        int* new_joltage = malloc(m.n_joltage * sizeof(int));
        for (int i = 0; i < m.n_joltage; i++){
            new_joltage[i] = joltage[i] / 2;
        }
        mini = 2 * min_button(m, new_joltage);
        free(new_joltage);
    }

    int k;
    for (int i = 1; i <= m.n_button; i++) {
        n = 0;
        combinations(i, m.n_button, comb, &n, 0, 0);
        for (int j = 0; j < n; j++) {
            button = calloc(m.n_joltage, sizeof(int));
            k = 0;
            while (comb[j] != 0) {
                if (comb[j]%2 == 1) {
                    for (int l = 0; l < m.n_joltage; l++) {
                        if (m.button[k][l]) {
                            button[l]++;
                        }
                    }
                }
                comb[j] /= 2;
                k++;
            }

            int* new_joltage = malloc(m.n_joltage * sizeof(int));
            for (int l = 0; l < m.n_joltage; l++) {
                new_joltage[l] = joltage[l] - button[l];
                if (new_joltage[l] < 0 || new_joltage[l]%2 == 1) {
                    free(new_joltage);
                    break;
                }
                new_joltage[l] /= 2;
                if (l == m.n_joltage - 1){
                    temp = 2 * min_button(m, new_joltage) + i;
                    if (temp < mini) mini = temp;
                }
            }
            free(button);
        }
    }

    free(comb);
    return mini;
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

    int res = 0;
    int temp;
    for (int i = 0; i < n; i++) {
        int* joltages = malloc(m[i].n_joltage * sizeof(int));
        for (int k = 0; k < m[i].n_joltage; k++){
            joltages[k] = m[i].joltage[k];
        }
        res += min_button(m[i], joltages);
        free(joltages);
    }
    printf("%d\n", res);
    return 0;
}
