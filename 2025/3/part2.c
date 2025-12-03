#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_N 500

long int get_number(int* bank, int n_bank, int n) {
    int* res = malloc(n * sizeof(int));
    int prev = -1;
    for (int i = 0; i < n; i++) {
        long int max = 0;
        for (int j = prev + 1; j <= n_bank - (n - i); j++) {
            if (bank[j] > max) {
                max = bank[j];
                prev = j;
            }
        }
        res[i] = max;
    }
    
    long int power = 0;
    for (int i = 0; i < n; i++) {
        power += res[i] * pow(10, n - i - 1);
    }
    free(res);
    return power;
}




int main(){
    int number;
    int* bank = malloc(MAX_N * sizeof(int));
    int n_bank = 0;
    long int res = 0;

    while((number = getchar()) != EOF) {
        fseek(stdin, -1, SEEK_CUR);
        n_bank = 0;
        while((number = getchar()) != '\n') {
            number -= '0';
            bank[n_bank++] = number;
        }
        res += get_number(bank, n_bank, 12);
    }

    free(bank);

    printf("%ld\n", res);

    return 0;
}
