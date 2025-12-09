#include <stdio.h>
#include <stdlib.h>
#define MAX_ 1000

long int size_rec(long int a1, long int a2, long int b1, long int b2) {
    if (a1 < b1) {
        long int c = a1;
        a1 = b1;
        b1 = c;
    }
    if (a2 < b2) {
        long int c = a2;
        a2 = b2;
        b2 = c;
    }
    return ((1 + a1 - b1) * (1 + a2 - b2));
}

int check_rec(long int** rec, int n, int a, int b){
    long int x1 = (rec[a][0] > rec[b][0]) ? rec[b][0] : rec[a][0];
    long int x2 = (rec[a][0] < rec[b][0]) ? rec[b][0] : rec[a][0];
    long int y1 = (rec[a][1] > rec[b][1]) ? rec[b][1] : rec[a][1];
    long int y2 = (rec[a][1] < rec[b][1]) ? rec[b][1] : rec[a][1];

    for (int i = 0; i < n; i++) {
        long int n1 = (rec[i][0] > rec[(i+1)%n][0]) ? rec[(i+1)%n][0] : rec[i][0];
        long int n2 = (rec[i][0] < rec[(i+1)%n][0]) ? rec[(i+1)%n][0] : rec[i][0];
        long int m1 = (rec[i][1] > rec[(i+1)%n][1]) ? rec[(i+1)%n][1] : rec[i][1];
        long int m2 = (rec[i][1] < rec[(i+1)%n][1]) ? rec[(i+1)%n][1] : rec[i][1];
        
        if(n1 < x2 && n2 > x1 && m1 > y1 && m2 < y2) {
            return 0;
        }
        if(m1 < y2 && m2 > y1 && n1 > x1 && n2 < x2) {
            return 0;
        }
    }
    return 1;
}

int main() {
    long int** rec = malloc(MAX_ * 2 * sizeof(long int));
    int n = -1;

    do {
        n++;
        rec[n] = malloc(2 * sizeof(long int));
    } while(scanf("%ld,%ld\n", &rec[n][0], &rec[n][1]) > 0);

    long int max = 0;
    long int size;

    long int a1, a2, b1, b2;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (!check_rec(rec, n, i, j)) continue;
            size = size_rec(rec[i][0], rec[i][1], rec[j][0], rec[j][1]);
            if (size > max) max = size;
        }
    }
    printf("%ld\n", max);
    

    return 0;
}
