#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int dist;
    char dir;
    int i;
    int j;
    struct node** pred;
    int n;
    int used;
} node_t;

void new_node(node_t** graph, int n, int i, int j, char dir) {
    graph[n] = malloc(sizeof(node_t));
    graph[n]->dist = -1;
    graph[n]->dir = dir;
    graph[n]->i = i;
    graph[n]->j = j;
    graph[n]->pred = malloc(200 * 200 * 4 * sizeof(node_t));
    graph[n]->n = 0;
    graph[n]->used = 0;
}

void sommet_min(node_t** graph, int n, node_t** res) {
    int min = -1;
    for (int i = 0; i < n; i++) {
        if (!graph[i]->used) {
            if (min == -1 || (graph[i]->dist != -1 && graph[i]->dist < min)) {
                min = graph[i]->dist;
                *res = graph[i];
            }
        }
    }

}

void best_path(node_t** graph, int n) {
    int n_p = 0;
    node_t* s;

    while (n_p < n) {
        sommet_min(graph, n, &s);

        s->used = 1;
        n_p++;
        for (int i = 0; i < n; i++) {
            if (!graph[i]->used){
                if (s->i == graph[i]->i && s->j == graph[i]->j) {
                    if (graph[i]->dist == -1 || graph[i]->dist > s->dist + 1000) {
                        graph[i]->dist = s->dist + 1000;
                        graph[i]->pred[0] = s;
                        graph[i]->n = 1;
                    }
                    else if (graph[i]->dist == s->dist + 1000) {
                        graph[i]->pred[graph[i]->n++] = s;
                    }
                }
                else if (s->dir == graph[i]->dir) {
                    if ((s->dir == 'N' && s->i == graph[i]->i + 1 && s->j == graph[i]->j) || (s->dir == 'E' && s->j == graph[i]->j - 1 && s->i == graph[i]->i) || (s->dir == 'O' && s->j == graph[i]->j + 1 && s->i == graph[i]->i) || (s->dir == 'S' && s->i == graph[i]->i - 1 && s->j == graph[i]->j)) {
                        if (graph[i]->dist == -1 || graph[i]->dist > s->dist + 1) {
                            graph[i]->dist = s->dist + 1;
                            graph[i]->pred[0] = s;
                            graph[i]->n = 1;
                        }
                        else if (graph[i]->dist == s->dist + 1) {
                            graph[i]->pred[(graph[i]->n)++] = s;
                        }
                    }
                }
            }
        }
    }
}

int n_path(int** map, node_t* N){
    int total = 1;
    if (map[N->i][N->j]) total = 0;

    map[N->i][N->j] = 1;
    for (int j = 0; j < N->n; j++) {
        total += n_path(map, N->pred[j]);
    }
    return total;
}

int main() {
   char** map = malloc(200 * 200 * sizeof(char));
   int n = 0;
   int m = 0;

   while(getchar() != EOF) {
       fseek(stdin, -1, SEEK_CUR);
       map[n] = malloc(200 * sizeof(char));
       fgets(map[n], 200, stdin);
       n++;
    }
    for (m = 0; map[0][m] != '\n'; m++);

    node_t** graph = malloc(200 * 200 * 4 * sizeof(node_t));
    int n_graph = 0;
    int x, y;


    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if(map[i][j] == '#') continue;
            if (map[i][j] == 'E') {
                x = i;
                y = j;
            }

            new_node(graph, n_graph, i, j, 'E');
            if (map[i][j] == 'S') {
                graph[n_graph]->dist = 0;
            }
            n_graph++;
            new_node(graph, n_graph, i, j, 'N');
            n_graph++;
            new_node(graph, n_graph, i, j, 'S');
            n_graph++;
            new_node(graph, n_graph, i, j, 'O');
            n_graph++;
        }
    }


    best_path(graph, n_graph);

    int total = -1;
    node_t* N;

    int** map2 = malloc(200 * 200 * sizeof(int));
    for (int i = 0; i < n; i++) {
        map2[i] = malloc(200 * sizeof(int));
        for (int j = 0; j < m; j++) {
            map2[i][j] = 0;
        }
    }

    for (int i = 0; i < n_graph; i++) {
        if (graph[i]->i == x && graph[i]->j == y) {
            if (total == -1 || graph[i]->dist < total) {
                total = graph[i]->dist;
                N = graph[i];
            }
        }
    }

    printf("%d\n", total);

    total = n_path(map2, N);

    printf("%d\n", total);
    return 0;
}
