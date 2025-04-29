#include <stdio.h>
#include <stdlib.h>

int has_tls(char* ip) {
    int result = 0;
    for (int i = 0; ip[i+3] != '\n'; i++) {
        if (ip[i] == '[') {
            for(i++; ip[i] != ']'; i++) {
                if (ip[i] == ip[i + 3] && ip[i + 1] == ip[i + 2] && ip[i] != ip[i + 1]) {
                    return 0;
                }
            }
        }
        if (ip[i] == ip[i + 3] && ip[i + 1] == ip[i + 2] && ip[i] != ip[i + 1]) {
            result = 1;
        }
    }
    return result;
}

int main() {
    char* ip = malloc(200 * sizeof(char));

    int nb_tls = 0;
    while(fgets(ip, 200, stdin)) {
        nb_tls += has_tls(ip);
    }
    printf("%d\n", nb_tls);
    return 0;
}
