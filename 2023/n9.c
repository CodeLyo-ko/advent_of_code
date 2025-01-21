#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int pascal(int n, int k){
    if (!k){
        return 1;
    }
    else {
        return pascal(n, k - 1) * (n - k +1) / k;
    }

}

int main(){
    int* input = malloc(1000 * sizeof(int*));
    int n;
    char c = getchar();
    int res = 0;
    while(c != EOF){
        n = 0;
        while (c != EOF && c != '\n'){
            fseek(stdin, -1, SEEK_CUR);
            scanf("%d", &input[n++]);
            c = getchar();
        }
        if ( c != EOF){
            c = getchar();
        }

        int val = input[0];
        int tmp;
        for (int i = 1; i < n; i++){
            tmp = 0;
            for (int j = 0; j <= i; j++){
                tmp += ((j%2)?-1:1) * pascal(i, j) * input[i-j];
            }
            val += (i%2?-1:1) * tmp;
        };
        res += val;
    }

    printf("%d\n", res);


}