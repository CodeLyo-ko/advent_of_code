#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_ 10000

void swap_pos(char* password, int a, int b) {
    int temp = password[a];
    password[a] = password[b];
    password[b] = temp;
}

void swap_let(char* password, char a, char b) {
    int size = strlen(password);
    for (int i = 0; i < size; i++) {
        if (password[i] == a) {
            password[i] = b;
        }
        else if (password[i] == b) {
            password[i] = a;
        }
    }
}

void rot_dir(char* password, int dir, int a) {
    int size = strlen(password);
    char temp = password[0];

    if (dir == 1) {
        for (int i = 0; i < a; i++) {
            temp = password[size - 1];
            for (int j = size - 1; j > 0; j--) {
                password[j] = password[j - 1];
            }
            password[0] = temp;
        }
    }
    else {
        for (int i = 0; i < a; i++) {
            temp = password[0];
            for (int j = 0; j < size - 1; j++) {
                password[j] = password[j + 1];
            }
            password[size - 1] = temp;
        }
    }
}

void rot_pos(char* password, char a) {
    int size = strlen(password);
    int index;
    for (int i = 0; i < size; i++) {
        if (password[i] == a) {
            index = i;
            break;
        }
    }
    if (index >=4) index++;
    index++;

    rot_dir(password, 1, index);
}

void reverse (char* password, int a, int b) {
    char temp;
    for (int i = a; i <= (a + b) / 2; i++) {
        temp = password[i];
        password[i] = password[b - (i - a)];
        password[b - (i - a)] = temp;
    }
}

void move(char* password, int a, int b) {
    char temp = password[a];
    if (a > b) {
        for (int i = a; i > b; i--) {
            password[i] = password[i - 1];
        }
        password[b] = temp;
    }
    else {
        for (int i = a; i < b; i++) {
            password[i] = password[i + 1];
        }
        password[b] = temp;
    }
}

void do_step(char* inst, char* password) {
    char word[MAX_];
    sscanf(inst, "%s", word);

    char tmp[MAX_];
    int i_a, i_b;
    char c_a, c_b;
    if (!strcmp(word, "swap")) {
        sscanf(inst, "%s %s", tmp, word);
        if (!strcmp(word, "position")) {
            sscanf(inst, "swap position %d with position %d", &i_a, &i_b);
            swap_pos(password, i_a, i_b);
        }
        else if (!strcmp(word, "letter")) {
            sscanf(inst, "swap letter %c with letter %c", &c_a, &c_b);
            swap_let(password, c_a, c_b);
        }
    }
    else if (!strcmp(word, "rotate")) {
        sscanf(inst, "%s %s", tmp, word);
        if (!strcmp(word, "based")) {
            sscanf(inst, "rotate based on position of letter %c", &c_a);
            rot_pos(password, c_a);
        }
        else if (!strcmp(word, "left")) {
            sscanf(inst, "rotate left %d steps", &i_a);
            rot_dir(password, -1, i_a);
        }
        else if (!strcmp(word, "right")) {
            sscanf(inst, "rotate right %d steps", &i_a);
            rot_dir(password, 1, i_a);
        }
    }
    else if (!strcmp(word, "reverse")) {
        sscanf(inst, "reverse positions %d through %d", &i_a, &i_b);
        reverse(password, i_a, i_b);
    }
    else if (!strcmp(word, "move")) {
        sscanf(inst, "move position %d to position %d", &i_a, &i_b);
        move(password, i_a, i_b);
    }

}

int main() {
    char* password = calloc(MAX_, sizeof(char));

    //example
    //sprintf(password, "abcde");
    //input
    sprintf(password, "abcdefgh");
    
    char* buff = NULL;
    size_t size;
    while(getchar() != EOF) {
        fseek(stdin, -1, SEEK_CUR);
        getline(&buff, &size, stdin);
        do_step(buff, password);
    }

    printf("%s\n", password);
    return 0;
}
