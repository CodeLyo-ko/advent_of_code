#include <stdio.h>
#include <stdlib.h>

#define diff(a, b) a>b?a-b:b-a

int comp_int(const void* a, const void* b) {

    return *(int*)a - *(int*)b;
}

int main() {
    int* list_1 = malloc(1001 * sizeof(int));
    int n = 0;
    int* list_2 = malloc(1001 * sizeof(int));

    while (scanf("%d %d", &list_1[n], &list_2[n]) != EOF){
        n++;
    }

    qsort(list_1, n, sizeof(int), &comp_int);
    qsort(list_2, n, sizeof(int), &comp_int);
    
    int total_distance = 0;

    for (int i = 0; i < n; i++) {
        total_distance += diff(list_1[i], list_2[i]);
    }

    printf("%d\n", total_distance);

    return 0;
}
