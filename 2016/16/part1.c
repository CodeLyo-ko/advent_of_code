#include <stdio.h>
#include <stdlib.h>
#define MAX_ 500

void generate(int* a, int* len_a, int size) {
    if (*len_a >= size) {
        *len_a = size;
        return;
    }

    a[*len_a] = 0;
    for (int i = 0; i < *len_a; i++) {
        a[(*len_a)* 2 - i] = !a[i]; 
    }
    *len_a = *len_a * 2 + 1;
    generate(a, len_a, size);
}

void checksum(int* a, int* len_a) {
    if (*len_a % 2) {
        return;
    }
    for (int i = 0; i < *len_a; i++) {
        a[i] = a[i * 2] == a[i * 2 + 1];
    }
    *len_a /= 2;
    checksum(a, len_a);
}

void print_arr(int* a, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d", a[i]);
    }
    printf("\n");
}


int main() {
    //example
    /*
    int size = 20;
    int* a = malloc(MAX_ * sizeof(int));
    int temp[5] = {1, 0, 0, 0, 0};
    int len_a = 5;
    */

    //input
    int size = 272;
    int* a = malloc(MAX_ * sizeof(int));
    int temp[17] = {0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0};
    int len_a = 17;

    for (int i = 0; i < len_a; i++) {
        a[i] = temp[i];
    }

    generate(a, &len_a, size);
    checksum(a, &len_a);
    print_arr(a, len_a);



    return 0;
}
