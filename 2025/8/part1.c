#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#define MAX_ 2000
#define N_PAIR 1000

typedef struct {
    int arr[MAX_];
    int back;
    int front;
} queue;

void initQueue(queue* q) {
    q->front = 0;
    q->back = 0;
}

int dequeue(queue* q) {
    return q->arr[(q->front)++];
}

void enqueue(queue* q, int val) {
    q->arr[(q->back)++] = val;
}

int isEmpty(queue* q) {
    return q->front == q->back;
}


int in_array(int* arr, int n, int k) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == k) return 1;
    }
    return 0;
}

int comp(const void* a, const void* b) {
    return *(int*)b - *(int*)a;
}

int comp_d(const void* a, const void* b) {
    long int* a_ = *(long int**)a;
    long int* b_ = *(long int**)b;
    if (a_[0] > b_[0]) {
        return 1;
    }
    if (a_[0] == b_[0]) {
        return 0;
    }
    if (a_[0] < b_[0]) {
        return -1;
    }
}


int main() {
    int** boxes = malloc(3 * MAX_ * sizeof(int));
    int n = -1;

    do {
        n++;
        boxes[n] = malloc(3 * sizeof(int));
    } while (scanf("%d,%d,%d\n", &boxes[n][0], &boxes[n][1], &boxes[n][2]) > 0);

    long int** distances = malloc(3 * n * n * sizeof(long int));
    int n_d = 0;

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            distances[n_d] = malloc(3 * sizeof(long int));
            distances[n_d][0] = sqrt(pow(boxes[i][0] - boxes[j][0], 2) + pow(boxes[i][1] - boxes[j][1], 2) + pow(boxes[i][2] - boxes[j][2], 2)); 
            distances[n_d][1] =(long int)i;
            distances[n_d][2] = (long int)j;
            n_d++;
        }
    }

    qsort(distances, n_d, sizeof(*distances), comp_d);


    int** g = malloc(N_PAIR * n * sizeof(int));
    int* n_g = calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) {
        g[i] = malloc(N_PAIR * sizeof(int));
    }

    int n1, n2;
    for (int k = 0; k < N_PAIR; k++) {
        n1 = distances[k][1];
        n2 = distances[k][2];
        g[n1][n_g[n1]++] = n2;
        g[n2][n_g[n2]++] = n1;
    }

    int* seen = calloc(n, sizeof(int));
    int* circuits = malloc(n * sizeof(int));
    int n_circuit = 0;

    for (int i = 0; i < n; i++) {
        if (seen[i]) continue;
        circuits[n_circuit] = 0;
        queue* Q = malloc(sizeof(queue));
        initQueue(Q);
        enqueue(Q, i);
        while(!isEmpty(Q)) {
            int v = dequeue(Q);
            if (seen[v]) continue;
            seen[v] = 1;
            circuits[n_circuit]++;
            for (int k = 0; k < n_g[v]; k++) {
                enqueue(Q, g[v][k]);
            }
        }
        free(Q);
        n_circuit++;
    }

    qsort(circuits, n_circuit, sizeof(*circuits), comp);

    printf("%ld\n", circuits[0] * circuits[1] * circuits[2]);
    return 0;
}
