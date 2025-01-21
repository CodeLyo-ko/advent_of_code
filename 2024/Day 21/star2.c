#include <stdio.h>
#include <stdlib.h>
#include "uthash.h"

typedef struct {
    char code[100];
    int level;
} hash_key_t;

typedef struct {
    hash_key_t key;
    long long res;
    UT_hash_handle hh;
} hash_t;

void cache(hash_t** hash_tab, char* code, int n, int level, long long res) {
    hash_t* item = malloc(sizeof(hash_t));
    memset(item, 0, sizeof *item);
    for (int k = 0; k < n; k++) {
        item->key.code[k] = code[k];
    }
    item->key.code[n] = '\0';
    item->key.level = level;
    // printf("%s %d\n", item->key.code, item->key.level);
    item->res = res;

    HASH_ADD(hh, *hash_tab, key, sizeof(hash_key_t), item);
}

int in_cache(hash_t** hash_tab, char* code, int n, int level, long long* res) {
    hash_t feur, * item, *test = NULL;
    // HASH_ITER(hh, *hash_tab, item, test) {
    //         // printf("%s %d\n", item->key.code, item->key.level);
    //
    // }
    memset(&feur, 0, sizeof(hash_t));
    for (int k = 0; k < n; k++) {
        feur.key.code[k] = code[k];
    }
    feur.key.level = level;
    feur.key.code[n] = '\0';
    HASH_FIND(hh, *hash_tab, &feur.key, sizeof(hash_key_t), item);
    if (!item) return 0;
    else {
    // printf("%s %d\n", item->key.code, item->key.level);
        *res = item->res;
        return 1;
    }
}

void copy(char* t1, char* t2, int n) {
    for (int i = 0; i < n; i++) {
        t2[i] = t1[i];
    }
}

void print_tab(char* t, int n) {
    for (int i = 0; i < n; i++) {
        printf("%c", t[i]);
    }
    printf("\n");
}

void input_keypad(char** keypad, int r, char prev, char now, char* input, int* n){
    if (prev == now) {
        input[(*n)++] = 'A';
        return;
    }

    int x, y, x2, y2;

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < 3; j++) {
    // printf("%c %c %c\n", keypad[i][j], prev,now);
            if (keypad[i][j] == prev) {
                x = i; y = j;
            }
            if (keypad[i][j] == now) {
                x2 = i; y2 = j;
            }
        }
    }
    // printf("%d　%d %d %d\n", x,  y, x2, y2);


    int h_first = 0;

    if (keypad[x][y2] == '\0') h_first = 0;
    else if (keypad[x2][y] == '\0') h_first = 1;
    else if (y2 < y && x2 < x) {
        h_first = 1;
    }
    else if (x2 < x && y2 > y) h_first = 0;
    else if (x2 > x && y2 < y) h_first = 1;
    else if (x2 > x && y2 > y) h_first = 0;

    if (h_first) {
        while (y2 > y) {
            input[(*n)++] = '>';
            y++;
        }
        while(y2 < y) {
            input[(*n)++] = '<';
            y--;
        }

    }
    while (x2 > x) {
        input[(*n)++] = 'v';
        x++;
    }
    while (x2 < x) {
        input[(*n)++] = '^';
        x--;
    }
    while (y2 > y) {
        input[(*n)++] = '>';
        y++;
    }
    while(y2 < y) {
        input[(*n)++] = '<';
        y--;
    }

    input[(*n)++] = 'A';
}

long long solve(hash_t** hash_tab, char** keypad, char* code, int n, int level, int level_max) {
    long long res = 0;
    // printf("%s %d\n", code, level);
    if (in_cache(hash_tab, code, n, level, &res)) {
        // printf("%d\n", level);
        return res;
    }

    if (level > level_max) {
        // printf("%d\n", n);
        return n;
    }


    char prev = 'A';
    char* new_code = malloc(100 * sizeof(char));
    int new_n = 0;

    for (int i  = 0; i < n; i++) {
        new_n = 0;
// printf("feur\n");
        input_keypad(keypad, 2, prev, code[i], new_code, &new_n);
        new_code[new_n] = '\0';
    // printf("%s %d %d\n", new_code, new_n, level);
        res += solve(hash_tab, keypad, new_code, new_n, level + 1, level_max);
        prev = code[i];
    }

    // printf("%d\n", res);
    cache(hash_tab, code, n, level, res);
    return res;
}

int main() {
    char* code = malloc(5 * sizeof(char));

    char** keypad_num = malloc(4 * 4 * sizeof(char));
    for (int i = 0; i < 3; i++) {
        keypad_num[i] = malloc(4 * sizeof(char));
        for (int j = 0; j < 3; j++) {
            keypad_num[i][j] ='0'  + j+ 1 + (6 -(3 *i));
        }
    }
    keypad_num[3] = malloc(4 * sizeof(char));
    keypad_num[3][0] = '\0';
    keypad_num[3][1] = '0';
    keypad_num[3][2] = 'A';

    char** keypad_dir = malloc(2 * 4 * sizeof(char));
    keypad_dir[0] = malloc(4 * sizeof(char));
    keypad_dir[0][0] = '\0';
    keypad_dir[0][1] = '^';
    keypad_dir[0][2] = 'A';
    keypad_dir[1] = malloc(4 * sizeof(char));
    keypad_dir[1][0] = '<';
    keypad_dir[1][1] = 'v';
    keypad_dir[1][2] = '>';

    char* input = malloc(200 * sizeof(char));
    int n = 0;
    char* input2 = malloc(200 * sizeof(char));
    int n2 = 0;

    hash_t* hash_tab = NULL;

    long long total = 0;

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 4; j++) {
            code[j] = getchar();
        }
        getchar();
        code[4] = '\0';
        char prev = 'A';
        n = 0;

        for (int j = 0; j < 4; j++) {
            input_keypad(keypad_num, 4, prev, code[j], input, &n);
            prev = code[j];
        }

        // print_tab(input, n);

        long long res = solve(&hash_tab, keypad_dir, input, n, 1, 25);
        printf("%s %lld\n", code, res);

        total += ((code[0] - '0') * 100 + (code[1] - '0') * 10 + (code[2] - '0')) * res;
    }

    printf("%lld\n", total);
}
