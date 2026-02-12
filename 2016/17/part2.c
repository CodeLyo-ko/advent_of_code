#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/md5.h>
#define MAX_ 10000
#define SIZE 4

#define MAX_QUEUE 10000000

typedef struct {
    char* path;
    int n;
    int x;
    int y;
} state_t;

state_t* queue[MAX_QUEUE];
int front = 0, back = 0;

void enqueue (state_t* state) {
    queue[back++] = state;
}

state_t* dequeue() {
    return queue[front++];
}

int is_queue_empty() {
    return front == back;
}

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

void get_hash(const char* salt, char* path, int n, char* result) {
    MD5_CTX md5_ctx;

    MD5_Init(&md5_ctx);
    MD5_Update(&md5_ctx, salt, strlen(salt));
    MD5_Update(&md5_ctx, path, n);
    hex_digest(&md5_ctx, result);
}

int is_open(char c) {
    return (c == 'b' || c == 'c' || c == 'd' || c == 'e' || c == 'f');
}

void copy_str (char* s1, char* s2, int n) {
    for (int i = 0; i < n; i++) {
        s1[i] = s2[i];
    }
}

int longest_path(char* salt, state_t* initial, int x_exit, int y_exit) {
    enqueue(initial);

    int max = 0;

    while (!is_queue_empty()) {
        state_t* curr = dequeue();
        int x = curr->x;
        int y = curr->y;
        char* path = curr->path;
        int n = curr->n;

        if (x == x_exit && y == y_exit) {
            if (n > max) {
                max = n;
            }
            free(path);
            free(curr);
            continue;
        }

        char* hash = malloc(MD5_DIGEST_LENGTH * 2);
        get_hash(salt, path, n, hash);

        if (x > 0 && is_open(hash[0])) {
            state_t* new_state = malloc(sizeof(state_t));
            new_state->x = x - 1;
            new_state->y = y;
            new_state->path = malloc((n + 3) * sizeof(char));
            copy_str(new_state->path, path, n);
            new_state->path[n] = 'U';
            new_state->path[n+1] = '\0';
            new_state->n = n + 1;
            enqueue(new_state);
        }
        if (x < SIZE - 1 && is_open(hash[1])) {
            state_t* new_state = malloc(sizeof(state_t));
            new_state->x = x + 1;
            new_state->y = y;
            new_state->path = malloc((n + 3) * sizeof(char));
            copy_str(new_state->path, path, n);
            new_state->path[n] = 'D';
            new_state->path[n+1] = '\0';
            new_state->n = n + 1;
            enqueue(new_state);
        }
        if (y > 0 && is_open(hash[2])) {
            state_t* new_state = malloc(sizeof(state_t));
            new_state->x = x;
            new_state->y = y - 1;
            new_state->path = malloc((n + 3) * sizeof(char));
            copy_str(new_state->path, path, n);
            new_state->path[n] = 'L';
            new_state->path[n+1] = '\0';
            new_state->n = n + 1;
            enqueue(new_state);
        }
        if (y < SIZE - 1 && is_open(hash[3])) {
            state_t* new_state = malloc(sizeof(state_t));
            new_state->x = x;
            new_state->y = y + 1;
            new_state->path = malloc((n + 3) * sizeof(char));
            copy_str(new_state->path, path, n);
            new_state->path[n] = 'R';
            new_state->path[n+1] = '\0';
            new_state->n = n + 1;
            enqueue(new_state);
        }
        free(hash);
        free(path);
        free(curr);
    }

    return max;
}

int main(){
    //examples
    //char salt[9] = "ihgpwlah";
    //char salt[9] = "kglvqrro";
    //char salt[9] = "ulqzkmiv";
    //input
    char salt[9] = "awrkjxxr";
    
    state_t* init = malloc(sizeof(state_t));
    init->x = 0;
    init->y = 0;
    init->n = 0;
    init->path = malloc( 5 *  sizeof(char));
    init->path[0] = '\0';

    int n = longest_path(salt, init, SIZE - 1, SIZE - 1);
    printf("%d\n", n);

    return 0;
}
