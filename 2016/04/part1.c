#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int id(char* room) {
    int i;
    for (i = 0; !isdigit(room[i]); i++);
    return strtol(&room[i], NULL, 10);
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
    int id_sum = 0;
    while(fgets(room, 100, stdin) != NULL) {
        id_sum += id(room) * is_room(room);
    }
    printf("%d\n", id_sum);
    return 0;
}
