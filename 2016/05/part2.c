#include <stdio.h>
#include <stdlib.h>
#include "md5.h"

int is_valid(uint8_t* hashed) {
    return (hashed[0] == 0 && hashed[1] == 0 && hashed[2] < 16);
}

char* concat(char* str, int i) {
    char* result = malloc(100 * sizeof(char));
    sprintf(result, "%s%d", str, i);
    return result;
}

uint8_t* hash(char* id, int i) {
   uint8_t* hashed = malloc(50 * sizeof(uint8_t));
   char* full_id = concat(id, i);
   md5String(full_id, hashed);
   return hashed;
}

uint8_t get_hex(uint8_t* n, int pos) {
    if (pos%2) {
        return n[pos/2]%16;
    }
    else {
        return n[pos/2]/16;
    }
}

static void printArray(const uint8_t *string)
{
    for (int i = 0; i < 8; i++) {
        printf("%x", string[i]);
    }
    printf("\n");
}

int main(){
    char* door_id = malloc(20 * sizeof(char));
    fgets(door_id, 20, stdin);
    door_id[strlen(door_id) - 1] = '\0'; //remove newline 
    int n_char = 0;
    uint8_t* hashed;
    uint8_t password[8];
    int* password_found = calloc(8, sizeof(int));
    for (int i = 0; n_char < 8; i++) {
       hashed = hash(door_id, i);
       if (is_valid(hashed)) {
           int pos = get_hex(hashed, 5);
           if (pos >= 0 && pos < 8 && !password_found[pos]) {
               password[pos] = get_hex(hashed, 6);
               n_char++;
               password_found[pos] = 1;
           }
       }
       free(hashed);
    }
    printArray(password);
    return 0;
}
