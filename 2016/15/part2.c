#include <stdio.h>
#include <stdlib.h>

int main() {
    //int size[2] = {5, 2};
    //int pos[2] = {0, 1};

    int size[7] = {19, 17, 13, 11, 7, 5, 3};
    int pos[7] = {19 - 5, 17 - 2, 13 - 11, 11 - 7, 7 - 2, 5 - 4, 3 - 2};

    //int n = 2;
    int n = 7;

    long int k = pos[0];
    long int m = size[0];
    for (int i = 1; i < n; i++) {
        while (k%size[i] != pos[i]) {
            k += m;
        }
        m *= size[i];
    }
    printf("%ld\n", k);

}


