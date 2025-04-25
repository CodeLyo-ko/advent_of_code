#include <stdio.h>
#include <stdlib.h>

int is_triangle(int a, int b, int c) {
    return (a + b > c) && (a + c > b) && (b + c > a);
}
            

int main() {
    int a1, b1, c1;
    int a2, b2, c2;
    int a3, b3, c3;
    int nb_triangle = 0;
    while(getchar() != EOF) {
        fseek(stdin, -1, SEEK_CUR);
        scanf("%d %d %d\n", &a1, &a2, &a3);
        scanf("%d %d %d\n", &b1, &b2, &b3);
        scanf("%d %d %d\n", &c1, &c2, &c3);
        nb_triangle += is_triangle(a1, b1, c1);
        nb_triangle += is_triangle(a2, b2, c2);
        nb_triangle += is_triangle(a3, b3, c3);
    } 
    printf("%d\n", nb_triangle);
    return 0;
}

