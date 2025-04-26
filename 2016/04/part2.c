#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int id(char* room) {
    int i;
    for (i = 0; !isdigit(room[i]); i++);
    return strtol(&room[i], NULL, 10);
}

char* decrypt(char* room) {
    int id_room = id(room);
    int cipher = id_room % 26;
    char* decrypted = malloc(100 * sizeof(char));
    for (int i = 0; !isdigit(room[i]); i++) {
        if (room[i] == '-') {
            decrypted[i] =' ';
            continue;
        }

        decrypted[i] = room[i] - 'a';
        decrypted[i] += cipher;
        decrypted[i] %= 26;
        decrypted[i] += 'a';
    }
    return decrypted;
}

int is_room(char* room) {
    char letters[26] = {0};
    int i = 0;
    int n;
    while (room[i] != '[') {
        n = room[i] - 'a';
        if (n >= 0 && n < 26) {
            letters[n]++;
        }
        i++;
    }
    for (i++; room[i] != ']'; i++) {
        n = room[i] - 'a';
        for (int j = 0; j < n; j++) {
            if (letters[j] >= letters[n]) {
                return 0;
            }
        }
        for (int j = n + 1; j < 26; j++) {
            if (letters[j] > letters[n]) {
                return 0;
            }
        }
        letters[n] = -1;
    }
    return 1;
}

int main() {
    char* room = malloc(100 * sizeof(char));
    while(fgets(room, 100, stdin) != NULL) {
        if (is_room(room)) {
            char* decrypted = decrypt(room);
            if (!strncmp("northpole", decrypted, 9)) {
                printf("%d\n", id(room));
            }
        }
    }
    return 0;
}
