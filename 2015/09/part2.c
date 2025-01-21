#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct {
    char* city1;
    char* city2;
    int distance;
} arete_t;

void add_char(char** cities, int* n_city, char* city) {
    for (int i = 0; i < *n_city; i++) {
        if (!strcmp(cities[i], city)) {
            return;
        }
    }

    cities[*n_city] = strdup(city);
    (*n_city)++;
}

int distance(arete_t* graph, int n_graph, char** cities, int n_city, int* visited, int city) {
    visited[city] = 1;

    int max = 0;
    int temp;

    int n_visit = 0;

    for (int i = 0; i < n_city; i++) {
        if (visited[i]) {
            n_visit++;
            continue;
        }

        for (int j = 0; j < n_graph; j++) {
            if ((!strcmp(graph[j].city1, cities[city]) && !strcmp(graph[j].city2, cities[i])) || (!strcmp(graph[j].city2, cities[city]) && !strcmp(graph[j].city1, cities[i]))) {

                temp = graph[j].distance + distance(graph, n_graph, cities, n_city, visited, i);
                if (temp > max) max = temp;
            }
        }
    }
    visited[city] = 0;

    if (n_visit == n_city) {
        return 0;
    }

    return max;
}

int main() {
    arete_t* graph = malloc(100 * sizeof(arete_t));
    int n = 0;

    char** cities = malloc(100 * 50 * sizeof(char));
    int n_city = 0;

    int* visited = malloc(100 * sizeof(int));

    char* line = malloc(100 * sizeof(char));

    while (getchar() != EOF) {
        fseek(stdin, -1, SEEK_CUR);
        fgets(line, 100, stdin);

        graph[n].city1 = malloc(50 * sizeof(char));
        graph[n].city2 = malloc(50 * sizeof(char));

        sscanf(line, "%s to %s = %d\n", graph[n].city1, graph[n].city2, &graph[n].distance);
        add_char(cities, &n_city, graph[n].city1);
        add_char(cities, &n_city, graph[n].city2);
        n++;

    }

    for (int i = 0; i < n_city; i++) {
        visited[i] = 0;
    }

    int temp;
    int max = 0;

    for (int i = 0; i < n_city; i++) {
        temp = distance(graph, n, cities, n_city, visited, i);
        if (temp > max) max = temp;
    }

    printf("%d\n", max);


    return 0;
}
