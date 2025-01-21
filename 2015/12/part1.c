#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char* s = malloc(45000 * sizeof(char));
    fgets(s, 45000, stdin);

    int total_n = 0;
    int n;
    int i;
    int total = 0;
    while (1 == sscanf(s + total_n, "%*[^0123456789-]%d%n", &i, &n)) {
        total_n += n;
        total += i;
    }

    printf("%d\n", total);
    return 0;
}
