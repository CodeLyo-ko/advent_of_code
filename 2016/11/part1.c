#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N_OBJECTS 10
#define MAX_FLOOR 4
#define MAX_INT 1000000
#define MAX_VISITED 10000000
#define MAX_QUEUE 10000000

typedef enum {
    lithium,
    hydrogen,
    promethium,
    cobalt,
    curium,
    ruthenium,
    plutonium
} element_t;

typedef enum {
    chip,
    generator
} type_t;

typedef struct {
    element_t e;
    type_t t;
} object_t;

typedef struct {
    object_t floors[MAX_FLOOR][N_OBJECTS];
    int n_floors[MAX_FLOOR];
    int current_floor;
    int steps;
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

int safe (object_t floors[MAX_FLOOR][N_OBJECTS], int n_floors[MAX_FLOOR]) {
    for (int i = 0; i < MAX_FLOOR; i++) {
        for (int j = 0; j < n_floors[i]; j++) {
            if (floors[i][j].t == generator) {
                continue;
            }
            int has_gen = 0;
            int other_gen = 0;
            for (int k = 0; k < n_floors[i]; k++) {
                if (j == k) continue;
                if (floors[i][k].t == generator) {
                    if (floors[i][k].e == floors[i][j].e) {
                        has_gen = 1;
                    }
                    else {
                        other_gen = 1;
                    }
                }
            }
            if (other_gen && !has_gen) return 0;
        }
    }
    return 1;
}


char* serialize(state_t* s) {

    int pairs[7][2]; // [chip_floor, gen_floor]
    for (int e = 0; e < 7; e++) {
        pairs[e][0] = -1;
        pairs[e][1] = -1;
    }

    for (int floor = 0; floor < MAX_FLOOR; floor++) {
        for (int i = 0; i < s->n_floors[floor]; i++) {
            object_t o = s->floors[floor][i];
            if (o.t == chip) {
                pairs[o.e][0] = floor;
            }
            else {
                pairs[o.e][1] = floor;
            }
        }
    }

    int flat_pairs[7][2];
    int n = 0;
    for (int e = 0; e < 7; e++) {
        if (pairs[e][0] != -1 || pairs[e][1] != -1) {
            flat_pairs[n][0] = pairs[e][0];
            flat_pairs[n][1] = pairs[e][1];
            n++;
        }
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (flat_pairs[i][0] > flat_pairs[j][0] || (flat_pairs[i][0] == flat_pairs[j][0] && flat_pairs[i][1] > flat_pairs[j][1])) {
                int tmp0 = flat_pairs[i][0];
                int tmp1 = flat_pairs[i][1];
                flat_pairs[i][0] = flat_pairs[j][0];
                flat_pairs[i][1] = flat_pairs[j][1];
                flat_pairs[j][0] = tmp0;
                flat_pairs[j][1] = tmp1;
            }
        }
    }

    char* key = malloc(1024);
    int offset = 0;
    offset += sprintf(key + offset, "%d|", s->current_floor);
    for (int i = 0; i < n; i++) {
        offset += sprintf(key + offset, "%d,%d|", flat_pairs[i][0], flat_pairs[i][1]);
    }
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

int min_steps(state_t* initial) {
    enqueue(initial);

    while (!is_queue_empty()) {
        state_t* curr = dequeue();
        if (curr->n_floors[3] == N_OBJECTS) {
            return curr->steps;
        }

        char* key = serialize(curr);
        if (is_visited(key)) {
            free(key);
            continue;
        }
        mark_visited(key);

        int n = curr->n_floors[curr->current_floor];
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                int move_count = (i == j) ? 1 : 2;
                if (curr->floors[curr->current_floor][i].t != curr->floors[curr->current_floor][j].t && curr->floors[curr->current_floor][i].e != curr->floors[curr->current_floor][j].e) {
                    continue;
                }
                        

                //move up/down
                for (int dir = -1; dir <= 1; dir += 2) {
                    int next_floor = curr->current_floor + dir;
                    if (next_floor < 0 || next_floor >= MAX_FLOOR) continue;

                    // if there's nothing below, no need to go down
                    if (dir == -1) {
                        int has_item_below = 0;
                        for (int k = 0; k <= next_floor; k++) {
                            if (curr->n_floors[k] != 0) {
                                has_item_below = 1;
                            }
                        }
                        if (!has_item_below) continue;
                    }


                    state_t* new_state = malloc(sizeof(state_t));
                    *new_state = *curr;
                    new_state->current_floor = next_floor;
                    new_state->steps++;

                    // add items to next floor
                    int size_next_floor = new_state->n_floors[next_floor];
                    new_state->floors[next_floor][size_next_floor++] = curr->floors[curr->current_floor][i];
                    if (move_count == 2) {
                        new_state->floors[next_floor][size_next_floor] = curr->floors[curr->current_floor][j];
                    }
                    new_state->n_floors[next_floor] += move_count;

                    // remove items from current floor
                    for (int k = i + 1; k < j; k++) {
                        new_state->floors[curr->current_floor][k - 1] = curr->floors[curr->current_floor][k];
                    }
                    for (int k = j + 1; k < n; k++) {
                        new_state->floors[curr->current_floor][k - move_count] = curr->floors[curr->current_floor][k];
                    }
                    new_state->n_floors[curr->current_floor] -= move_count;

                    if (safe(new_state->floors, new_state->n_floors)) {
                        enqueue(new_state);
                    }
                    else {
                        free(new_state);
                    }
                }
            }
        }
        free(curr);
    }
    return -1;
}

int main() {

    state_t* initial = malloc(sizeof(state_t));
    initial->current_floor = 0;
    initial->steps = 0;

    // initial->floors[0][0] = (object_t){hydrogen, chip};
    // initial->floors[0][1] = (object_t){lithium, chip};
    // initial->n_floors[0] = 2;
    // 
    // initial->floors[1][0] = (object_t){hydrogen, generator};
    // initial->n_floors[1] = 1;

    // initial->floors[2][0] = (object_t){lithium, generator};
    // initial->n_floors[2] = 1;
    
    initial->floors[0][0] = (object_t){promethium, generator};
    initial->floors[0][1] = (object_t){promethium, chip};
    initial->n_floors[0] = 2;

    initial->floors[1][0] = (object_t){cobalt, generator};
    initial->floors[1][1] = (object_t){curium, generator};
    initial->floors[1][2] = (object_t){ruthenium, generator};
    initial->floors[1][3] = (object_t){plutonium, generator};
    initial->n_floors[1] = 4;

    initial->floors[2][0] = (object_t){cobalt, chip};
    initial->floors[2][1] = (object_t){curium, chip};
    initial->floors[2][2] = (object_t){ruthenium, chip};
    initial->floors[2][3] = (object_t){plutonium, chip};
    initial->n_floors[2] = 4;

    initial->n_floors[3] = 0;

    int result = min_steps(initial);
    printf("%d\n", result);
    return 0;
}
