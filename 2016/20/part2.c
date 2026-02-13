#include <stdio.h>
#include <stdlib.h>
//example
//#define MAX_IP 9
//input
#define MAX_IP 4294967295

#define MAX_ 10000

typedef struct {
    long int a;
    long int b;
} range_t;

int comp(const void *a, const void *b) {
    range_t a_ = *(range_t*)a;
    range_t b_ = *(range_t*)b;
    
    if (a_.a > b_.a) {
        return 1;
    }
    else return -1;
}

int main(){
    range_t* ranges = malloc(MAX_ * sizeof(range_t));
    int n_ranges = 0;

    long int a, b;
    while(getchar() != EOF) {
        fseek(stdin, -1, SEEK_CUR);
        scanf("%ld-%ld\n", &a, &b);
        range_t r;
        r.a = a;
        r.b = b;
        ranges[n_ranges++] = r;
    }

    qsort(ranges, n_ranges, sizeof(ranges[0]), comp);

    for (int i = 1; i < n_ranges; i++) {
        if (ranges[i].a < ranges[i - 1].b) {
            ranges[i].a = ranges[i - 1].b;
        }
        if (ranges[i].b < ranges[i - 1].b) {
            ranges[i].b = ranges[i - 1].b;
        }
    }

    long int res = ranges[0].a;

    for (int j = 1; j < n_ranges; j++) {
        if (ranges[j].a > ranges[j - 1].b + 1) {
            res += ranges[j].a - ranges[j - 1].b - 1;
        }
    }

    printf("%ld\n", res);

    return 0;
}
