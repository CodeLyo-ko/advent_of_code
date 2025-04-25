#include <stdio.h>
#include <stdlib.h>

int is_triangle(int a, int b, int c) {
    return (a + b > c) && (a + c > b) && (b + c > a);
}
            

int main() {
    int a, b, c;
    int nb_triangle = 0;
    while(getchar() != EOF) {
        fseek(stdin, -1, SEEK_CUR);
        scanf("%d %d %d\n", &a, &b, &c);
        nb_triangle += is_triangle(a, b, c);
    } 
    printf("%d\n", nb_triangle);
    return 0;
}

