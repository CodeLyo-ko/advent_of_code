#include <stdio.h>
#include <stdlib.h>

int has_ssl(char* ip) {
    for (int i = 0; ip[i + 2] != '\n'; i++) {
        if (ip[i] == '[') for (i++; ip[i] != ']'; i++);

        if (ip[i] == ip[i + 2] && ip[i] != ip[i + 1]) {
            for (int j = 0; ip[j] != '\n'; j++) {
                if (ip[j] == '[') {
                    for (j++; ip[j] != ']'; j++) {
                        if (ip[j] == ip[i + 1] && ip[j + 1] == ip[i] && ip[j + 2] == ip[i + 1]) {
                            return 1;
                        }
                    }
                }
            }
        }
    }
    return 0;
}

int main() {
    char* ip = malloc(200 * sizeof(char));

    int nb_tls = 0;
    while(fgets(ip, 200, stdin)) {
        nb_tls += has_ssl(ip);
    }
    printf("%d\n", nb_tls);
    return 0;
}
