#include <stdio.h>
#include <stdlib.h>
#define MAX_ 100000

int main(){
    long int** problem = malloc(2 * MAX_ * sizeof(long int));
    int n = 0;

    char c;
    while((c = getchar()) != '\n') {
        fseek(stdin, -1, SEEK_CUR);
        problem[n] = malloc(2 * sizeof(long int));
        scanf("%d", &problem[n][0]);
        problem[n][1] = problem[n][0];
        n++;
        c = getchar();
        if (c == '\n') break;
    }

    int k;
    while(( c = getchar()) != '*' && c != '+') {
        fseek(stdin, -1, SEEK_CUR);
        for (int i = 0; i < n; i++) {
            scanf("%d\n", &k);
            problem[i][0] += k;
            problem[i][1] *= k;
        }
    }
    fseek(stdin, -1, SEEK_CUR);

    long int res = 0;
    for (int i = 0; i < n; i++) {
        while ((c = getchar()) != '*' && c != '+');
        if (c == '*') {
            res += problem[i][1];
        }
        else {
            res += problem[i][0];
        }
       
    }

    printf("%ld\n", res);

    return 0;
}
