#include <stdio.h>
#include <stdlib.h>
#include "uthash.h"


typedef struct {
    char* string;
    int result;
    UT_hash_handle hh;
} cache_t;

void cache(cache_t** cache_tab, char* towel, int n, int i, int res) {
    cache_t* item = malloc(sizeof(cache_t));
    item->string = malloc(100 * sizeof(char));
    for (int k = i; k < n; k++) {
        item->string[k - i] = towel[k];
    }
    item->string[n - i] = '\0';
    item->result = res;

    HASH_ADD_KEYPTR(hh, *cache_tab, item->string, n - i, item);

}

int in_cache(cache_t** cache_tab, char* towel, int n, int i, int* res) {
    char* string = malloc(100 * sizeof(char));
    for (int k = i; k < n; k++) {
        string[k - i] = towel[k];
    }
    string[n - i] = '\0';
    cache_t* item;
    HASH_FIND_STR(*cache_tab, string, item);
    if (!item) return 0;
    else {
        *res = item->result;
        return 1;
    }
}

int is_possible(cache_t** cache_tab, char** designs, int n_design, int* k_design, char* towel, int n_towel, int i) {
    if (i == n_towel) return 1;
    int res;
    if (in_cache(cache_tab, towel, n_towel, i, &res)) {
        return res;
    }
    for (int n = 0; n < n_design; n++) {
        for (int k = 0; k < k_design[n]; k++) {
            if (designs[n][k] != towel[i + k]) {
                break;
            }
            if (k == k_design[n] - 1) {
                if (is_possible(cache_tab, designs, n_design, k_design, towel, n_towel, i + k_design[n])) {
                    cache(cache_tab, towel, n_towel, i, 1);
                    return 1;
                }
            }
        }
    }
    cache(cache_tab, towel, n_towel, i, 0);
    return 0;
}

int main() {
    char** designs = malloc(500 * 500 * sizeof(char));
    int n_design = 0;
    int* k_design = malloc(500 * sizeof(int));

    char* towel = malloc(500 * sizeof(char));
    int n_towel = 0;

    while(getchar() != '\n') {
        fseek(stdin, -1, SEEK_CUR);
        designs[n_design] = malloc(500 * sizeof(char));
        k_design[n_design] = 0;
        while(getchar() != ',') {
            fseek(stdin, -1, SEEK_CUR);
            designs[n_design][(k_design[n_design])++] = getchar();
        }
        getchar();
        n_design++;
    }


    int total = 0;

    while(getchar() != EOF) {
        fseek(stdin, -1, SEEK_CUR);
    cache_t* cache_tab = NULL;
        n_towel = 0;
        while(getchar() != '\n') {
            fseek(stdin, -1, SEEK_CUR);
            towel[n_towel++] = getchar();
        }
        towel[n_towel] = '\0';
       if( is_possible(&cache_tab, designs, n_design, k_design, towel, n_towel, 0)) {
           total++;
    }
    }

    printf("%d\n", total);
    return 0;
}
