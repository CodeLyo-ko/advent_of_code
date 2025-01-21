#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int n;
    long val;
    long score;
} cache_t;

int digit(long l) {
    long n = l;
    int total = 0;
    do {
        n /= 10;
        total++;
    } while (n != 0);
    return total;
}

void half_digit(long n, int* v1, int* v2) {
    int ten_power = 1;

    *v1 = 0;
    *v2 = 0;

    int d = digit(n);

    for (int i = 0; i < d / 2; i++) {
        *v1 += ten_power *(n%10) ;
        n /= 10;
        ten_power *= 10;
    }


    ten_power = 1;

    for (int i = 0; i < d / 2; i++) {
        *v2 += ten_power * (n % 10);
        n /= 10;
        ten_power *= 10;
    }
}



long score (long input, int n, cache_t** cache, int* n_cache) {
    for (int i = 0; i < *n_cache; i++) {
        //printf("%d %d\n", cache[i]->val, cache[i]->n);
        if (cache[i]->val == input && cache[i]->n == n) {
            //printf("%ld %d\n", input, cache[i]->score);
            return cache[i]->score;
        }
    }
    if (n == 0) {
    //printf("%ld %d\n", input, n);
        return 1;
    }

    long res;
    if (input == 0) {
        res = score(1, n-1, cache, n_cache);
        cache[*n_cache] = malloc(sizeof(cache_t));
        cache[*n_cache]->n = n;
        cache[*n_cache]->val = input;
        (*n_cache)++;
        cache[(*n_cache) - 1]->score = res;

    }
    else if (digit(input) % 2 == 0) {
        int n1, n2;
        half_digit(input, &n1, &n2);
        res = score(n1, n-1, cache, n_cache) + score(n2, n-1, cache, n_cache);
        cache[*n_cache] = malloc(sizeof(cache_t));
        cache[*n_cache]->n = n;
        cache[*n_cache]->val = input;
        (*n_cache)++;
        cache[(*n_cache) - 1]->score = res;
    }
    else {
        res = score(input * 2024, n-1, cache, n_cache);
        cache[*n_cache] = malloc(sizeof(cache_t));
        cache[*n_cache]->n = n;
        cache[*n_cache]->val = input;
        (*n_cache)++;
        cache[(*n_cache) - 1]->score = res;
    }
    return res;
}



int main() {
    long* input = malloc(100 * sizeof(long));
    int n = 0;

    while(getchar() != '\n') {
        fseek(stdin, -1, SEEK_CUR);
        scanf("%d", &input[n++]);
    }

    long total = 0;

    cache_t** cache = malloc(200000 * sizeof(cache_t));
    int n_cache = 0;

    for (int i = 0; i < n; i++) {
        total += score(input[i],75, cache, &n_cache);
    }

    printf("%ld\n", total);


    return 0;
}
