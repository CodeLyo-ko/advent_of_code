#include <stdio.h>
#include <stdlib.h>
#define MAX_ 10000000

int main() {
    //example
    //int n_elves = 5;
    //input
    int n_elves = 3018458;

    int* elves = malloc(MAX_ * sizeof(int));
    for (int i = 1; i <= n_elves; i++) {
        elves[i] = 1;
    }

    int n_pres = n_elves;
    int i = 1;
    int j = 0;
    while (n_pres > 1) {
        while(elves[i] == 0){
            i++;
            i%=n_elves + 1;
        }
        j = i + 1;
        while(elves[j] == 0) {
            j++;
            j%=n_elves + 1;
        }
        elves[j] = 0;
        n_pres--;
        if(n_pres == 1) break;
        i++;
        i%=n_elves + 1;
    }

    printf("%d\n", i);



    return 0;
}
