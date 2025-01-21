#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "md5.h"
#include "md5.c"

void print_bytes(uint8_t bytes[16]) {
	for (int i = 0; i < 16; i++) {
		printf("%02x", bytes[i]);
	}
	printf("\n");
}

void md5_convert(char* input, uint8_t output[16]) {
    md5_context ctx;
	md5_init(&ctx);
	md5_digest(&ctx, input, strlen(input));
    md5_output(&ctx, output);
}

void int_to_str(int k, char* k_str) {
    sprintf(k_str, "%d", k);
}

void concat(char* key, int k, char* input) {
    int n = 0;
    for (int i = 0; i < strlen(key); i++) {
        input[i] = key[i];
        n++;
    }

    char* k_str = malloc(100 * sizeof(char));
    int_to_str(k, k_str);

    for (int i = 0; i < strlen(k_str); i++) {
        input[n] = k_str[i];
        n++;
    }

    input[n] = '\0';
}

int five_zeroes(uint8_t out[16]) {
    return ((out[0] ) == 0 && out[1] == 0 && out[2] == 0);
}

int main() {
    char* key = "bgvyzdsv";
    char* input =  malloc(200 * sizeof(char));

    uint8_t output[16];

    int stop = 0;
    for (int i = 1; !stop; i++) {
        concat(key, i, input);
        md5_convert(input, output);
        if (five_zeroes(output)) {
            stop = 1;
            printf("%d\n", i);
        }
    }


    return 0;
}
