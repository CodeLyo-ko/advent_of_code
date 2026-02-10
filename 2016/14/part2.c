#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/md5.h>
#define QUEUE_SIZE 1001

void hex_digest(MD5_CTX *md5_ctx, char* result) {
        char digits[] = "0123456789abcdef";
        uint8_t hash[MD5_DIGEST_LENGTH];
        int i;

        MD5_Final(hash, md5_ctx);

        for (i = 0; i < MD5_DIGEST_LENGTH; i++) {
                *(result++) = digits[hash[i] >> 4];
                *(result++) = digits[hash[i] & 0x0f];
        }
}

void get_hash(const char* salt, int index, char* result) {
    MD5_CTX md5_ctx;
    int len_index;
    char str_index[32];

    len_index = sprintf(str_index, "%i", index);

    MD5_Init(&md5_ctx);
    MD5_Update(&md5_ctx, salt, strlen(salt));
    MD5_Update(&md5_ctx, str_index, len_index);
    hex_digest(&md5_ctx, result);
    for(int i = 0; i < 2016; i++) {
        MD5_Init(&md5_ctx);
        MD5_Update(&md5_ctx, result, MD5_DIGEST_LENGTH * 2);
        hex_digest(&md5_ctx, result);
    }
}

void init_queue(char** queue, const char* salt) {
    for (int i = 0; i < QUEUE_SIZE; i++) {
        queue[i] = malloc(MD5_DIGEST_LENGTH * 2);
        get_hash(salt, i, queue[i]);
    }
}

int has_triplet(char* hash, char* c) {
    for (int i = 0; i <= MD5_DIGEST_LENGTH * 2 - 3; i++) {
        if (hash[i] == hash[i + 1] && hash[i] == hash[i + 2]) {
            *c = hash[i];
            return 1;
        }
    }
    return 0;
}

int has_quintuplet(char* hash, char c) {
    int res;
    for (int i = 0; i <= MD5_DIGEST_LENGTH * 2 - 5; i++) {
        if (hash[i] == c) {
            res = 1;
            for (int j = i + 1; j < i + 5; j++) {
                if (hash[j] != hash[i]) {
                    res = 0;
                    break;
                }
            }
            if (res) return 1;
        }
    }
    return 0;
}

int solve(const char* salt, int n_res) {
    char** queue = malloc(QUEUE_SIZE * MD5_DIGEST_LENGTH * 2);
    int i = 0;
    int i_q = 0;
    init_queue(queue, salt);
    int n = 0;
    char c;

    while (n < n_res) {
        if (has_triplet(queue[i_q], &c)) {
            for (int k = 0; k < QUEUE_SIZE; k++) {
                if (k == i_q) continue;
                if (has_quintuplet(queue[k], c)) {

                    n++;
                    break;
                }
            }
        }
        i++;
        get_hash(salt, i+QUEUE_SIZE, queue[i_q]);
        i_q++; i_q %= QUEUE_SIZE;
    }
    return i;
}
        
int main() {
    //const char* salt = "abc";
    const char* salt = "qzyelonm";

    int res = solve(salt, 64);
    printf("%d\n", res);

    return 0;
}
