#include <stdio.h>
#include <stdlib.h>
#define MAX_ 10000
#define MAX_QUEUE 100000000

typedef struct {
    int x;
    int y;
    int n_step;
} state_t;

state_t* queue[MAX_QUEUE];
int first = 0; int last = 0;

void init_queue() {
    first = 0;
    last = 0;
}

void enqueue(state_t* s) {
    queue[last++] = s;
}

state_t* dequeue() {
    return queue[first++];
}

int is_empty() {
    return first == last;
}

int shortest_route_2_point(state_t* initial, char** grid, int x, int y) {
    init_queue();
    enqueue(initial);

    while(!is_empty()) {
        state_t* curr = dequeue();

        if (grid[curr->x][curr->y] == '#') {
            free(curr);
            continue;
        }
        
        if (curr->x == x && curr->y == y) {
            return curr->n_step;
        }

        grid[curr->x][curr->y] = '#';

        state_t* new = malloc(sizeof(state_t));
        new->x = curr->x + 1;
        new->y = curr->y;
        new->n_step = curr->n_step + 1;
        enqueue(new);

        new = malloc(sizeof(state_t));
        new->x = curr->x - 1;
        new->y = curr->y;
        new->n_step = curr->n_step + 1;
        enqueue(new);
        
        new = malloc(sizeof(state_t));
        new->x = curr->x;
        new->y = curr->y + 1;
        new->n_step = curr->n_step + 1;
        enqueue(new);

        new = malloc(sizeof(state_t));
        new->x = curr->x;
        new->y = curr->y - 1;
        new->n_step = curr->n_step + 1;
        enqueue(new);
        
        free(curr);
    }
}

void get_permutation(int** res, int* arr, int* i, int l, int n) {
    if (l == n - 1) {
        res[*i] = malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            res[*i][j] = arr[j];
        }
        (*i)++;
        return;
    }
    int temp;
    for (int j = l; j < n; j++) {
        temp = arr[l];
        arr[l] = arr[j];
        arr[j] = temp;

        get_permutation(res, arr, i, l + 1, n);

        temp = arr[l];
        arr[l] = arr[j];
        arr[j] = temp;
    }
}

int shortest_path(int** paths, int n) {
    int** all_permutation = malloc(n * MAX_ * sizeof(int));

    int* first_perm = malloc(n * sizeof(int));
    for (int i = 1; i < n; i++) {
        first_perm[i - 1] = i;
    }
    int n_perm = 0;
    get_permutation(all_permutation, first_perm, &n_perm, 0, n - 1);

    int res;
    int min = MAX_;
    int x,y;
    for (int i = 0; i < n_perm; i++) {
        y = all_permutation[i][0];
        res = paths[0][y];
        for (int j = 1; j < n - 1; j++) {
            x = all_permutation[i][j - 1];
            y = all_permutation[i][j];
            res += paths[x][y];
        }
        x = all_permutation[i][n - 2];
        res += paths[x][0];
        if (res < min) {
            min = res;
        }
    }
    return min;
}

int main() {
    char** grid = malloc(MAX_ * MAX_ * sizeof(char));
    int n = 0;
    int m = 0;
    int n_numbers = 0;

    char c;
    while(getchar() != EOF) {
        fseek(stdin, -1, SEEK_CUR);
        m = 0;
        grid[n] = malloc(MAX_ * sizeof(char));
        while((c = getchar()) != '\n') {
            grid[n][m++] = c;
            if (c != '#' && c != '.') {
                n_numbers++;
            }
        }
        n++;
    }

    int** points = malloc(2 * n_numbers * sizeof(int));

    for (int i = 0; i < n_numbers; i++) {
        points[i] = malloc(2 * sizeof(int));
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] != '#' && grid[i][j] != '.') {
                int p = grid[i][j] - '0';
                points[p][0] = i;
                points[p][1] = j;
            }
        }
    }

    int** paths = malloc(n_numbers * n_numbers * sizeof(int));
    for (int i = 0; i < n_numbers; i++) {
        paths[i] = malloc(n_numbers * sizeof(int));
    }

    for (int i = 0; i < n_numbers; i++) {
        for (int j = i + 1; j < n_numbers; j++) {
            state_t* initial = malloc(sizeof(state_t));
            initial->x = points[i][0];
            initial->y = points[i][1];
            initial->n_step = 0;

            char** cp_grid = malloc(n * m * sizeof(char));
            for (int i = 0; i < n; i++) {
                cp_grid[i] = malloc(m * sizeof(char));
                for (int j = 0; j < m; j++) {
                    cp_grid[i][j] = grid[i][j];
                }
            }

            int res = shortest_route_2_point(initial, cp_grid, points[j][0], points[j][1]);
            free(cp_grid);
            paths[i][j] = res;
            paths[j][i] = res;
        }
    }

    int res = shortest_path(paths, n_numbers);
    printf("%d\n", res);
    return 0;
}
