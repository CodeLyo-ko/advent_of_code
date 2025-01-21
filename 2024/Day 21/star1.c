#include <stdio.h>
#include <stdlib.h>
#include "uthash.h"

typedef struct {
    char key[3];
    char* res;
    int n;
    UT_hash_handle hh;
} hash_t;

void cache(hash_t* hash_tab, char prev, char now, char* res, int n) {
    hash_t* item = malloc(sizeof(hash_t));
    item->res = malloc(100 * sizeof(char));
    for (int k = 0; k < n; k++) {
        item->res[k] = res[k];
    }
    item->res[n] = '\0';

    item->key[0] = prev;
    item->key[1] = now;
    item->key[2] = '\0';

    item->n = n;

    HASH_ADD_STR(hash_tab, key, item);

}

int in_cache(hash_t* hash_tab, char prev, char now, char* res, int* n) {
    char key[3];
    key[0] = prev; key[1] = now; key[2] = '\0';
    hash_t* item;
    HASH_FIND_STR(hash_tab, key, item);
    if (!item) return 0;
    else {
        res = item->res;
        *n = item->n;
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

void input_keypad(hash_t* hash_tab, char** keypad, int r, char prev, char now, char* input, int* n){
    char* res = malloc(100 * sizeof(char));
    int n_res = 0;
    if (in_cache(hash_tab, prev, now, res, &n_res)) {
        for (int i = 0; i < n_res; i++) {
            input[(*n)++] = res[i];
        }
        return;
    }

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
            res[n_res++] = '>';
            input[(*n)++] = '>';
            y++;
        }
        while(y2 < y) {
            res[n_res++] = '<';
            input[(*n)++] = '<';
            y--;
        }

    }
    while (x2 > x) {
        res[n_res++] = 'v';
        input[(*n)++] = 'v';
        x++;
    }
    while (x2 < x) {
        res[n_res++] = '^';
        input[(*n)++] = '^';
        x--;
    }
    while (y2 > y) {
        res[n_res++] = '>';
        input[(*n)++] = '>';
        y++;
    }
    while(y2 < y) {
        res[n_res++] = '<';
        input[(*n)++] = '<';
        y--;
    }

    res[n_res++] = 'A';
    input[(*n)++] = 'A';
    cache(hash_tab, prev, now, res, n_res);
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

    int total = 0;

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 4; j++) {
            code[j] = getchar();
        }
        getchar();
        code[4] = '\0';
        char prev = 'A';
        n = 0;

        for (int j = 0; j < 4; j++) {
            input_keypad(hash_tab, keypad_num, 4, prev, code[j], input, &n);
            prev = code[j];
        }

        // print_tab(input, n);

        for (int j = 0; j < 2; j++) {
            copy(input, input2, n);
            n2 = n;
            n = 0;
            prev = 'A';
            // print_tab(input2, n2);
            for (int j = 0; j < n2; j++) {
                input_keypad(hash_tab, keypad_dir, 2,  prev, input2[j], input, &n);
                prev = input2[j];
            }
            // print_tab(input, n);
        }

        printf("%s %d\n", code, n);

        total += ((code[0] - '0') * 100 + (code[1] - '0') * 10 + (code[2] - '0')) * n;
    }

    printf("%d\n", total);
}
