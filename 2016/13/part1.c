#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUEUE 10000
#define MAX_VISITED 100000

typedef struct {
    int x;
    int y;
    int step;
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

char* serialize(state_t* s) {
    char* key = malloc(1024);
    sprintf(key, "%d,%d", s->x, s->y);
    return key;
}

char* visited[MAX_VISITED];
int n_visited = 0;

int is_visited(char* key) {
    for (int i = 0; i < n_visited; i++) {
        if (!strcmp(visited[i], key)) {
            return 1;
        }
    }
    return 0;
}

void mark_visited(char* key) {
    if (n_visited < MAX_VISITED) {
        visited[n_visited++] = key;
    } 
    else {
        free(key);
    }
}

int number_of_bits(int x) {
    int res = 0;
    while (x > 0) {
        res += x % 2;
        x /= 2;
    }
    return res;
}

int is_open_space(int x, int y) {
    if (x < 0 || y < 0) return 0;

    int num = x * x + 3 * x + 2 * x * y + y + y * y;
    num += 1350; // input
    int res = number_of_bits(num);
    return !(res % 2);
}

int min_step(int x_dest, int y_dest, state_t* initial) {
    enqueue(initial);

    while (!is_queue_empty()) {
        state_t* curr = dequeue();

        int x = curr->x;
        int y = curr->y;

        if (x == x_dest && y == y_dest) {
            return curr->step;
        }

        char* key = serialize(curr);
        if (is_visited(key)) {
            free(key);
            continue;
        }
        mark_visited(key);

        if (is_open_space(x + 1, y)) {
            state_t* new_state = malloc(sizeof(state_t));
            new_state->x = x + 1;
            new_state->y = y;
            new_state->step = curr->step + 1;
            enqueue(new_state);
        }
        if (is_open_space(x - 1, y)) {
            state_t* new_state = malloc(sizeof(state_t));
            new_state->x = x - 1;
            new_state->y = y;
            new_state->step = curr->step + 1;
            enqueue(new_state);
        }
        if (is_open_space(x, y + 1)) {
            state_t* new_state = malloc(sizeof(state_t));
            new_state->x = x;
            new_state->y = y + 1;
            new_state->step = curr->step + 1;
            enqueue(new_state);
        }
        if (is_open_space(x, y - 1)) {
            state_t* new_state = malloc(sizeof(state_t));
            new_state->x = x;
            new_state->y = y - 1;
            new_state->step = curr->step + 1;
            enqueue(new_state);
        }
        free(curr);

    }
    return -1;
}

int main() {
    state_t* initial = malloc(sizeof(state_t));
    initial->x = 1;
    initial->y = 1;
    initial->step = 0;

    int result = min_step(31, 39, initial);
    printf("%d\n", result);
    return 0;
}
