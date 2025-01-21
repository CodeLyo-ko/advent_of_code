#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char name1;
    char name2;
    int happiness;
} arete_t;

void add_name(char* names, int* n_names, char name) {
    for (int i = 0; i < *n_names; i++) {
        if (names[i] == name) return;
    }
    names[*n_names] = name;
    (*n_names)++;
}

int compute_happiness(arete_t* graph, int n_graph, char* table, int n_table) {
    int happiness = 0;
    for (int i = 0; i < n_table; i++) {
        if (table[i] == 'i' || table[(i + 1) % n_table] == 'i') continue;
        for (int j = 0; j < n_graph; j++) {
            if (graph[j].name1 == table[i] && graph[j].name2 == table[(i + 1) % n_table]) {
                happiness += graph[j].happiness;
            }
            if (graph[j].name2 == table[i] && graph[j].name1 == table[(i + 1) % n_table]) {
                happiness += graph[j].happiness;
            }
        }
    }

    return happiness;
}

int compute_permutations(arete_t* graph, int n_graph, char* names, int n_names, int* taken, char* perm, int n_perm) {
    if (n_perm == n_names) {
        return compute_happiness(graph, n_graph, perm, n_perm);
    }

    int max = 0;
    int temp;

    for (int i = 0; i < n_names; i++) {
        if (taken[i]) continue;

        taken[i] = 1;
        perm[n_perm] = names[i];
        temp = compute_permutations(graph, n_graph, names, n_names, taken, perm, n_perm + 1);
        if (temp > max) max = temp;
        taken[i] = 0;
    }

    return max;
}

int main() {
    arete_t* graph = malloc(200 * sizeof(arete_t));
    int n_graph = 0;

    char* names = malloc(200 * sizeof(char));
    int n_names = 0;

    int* taken = malloc(200 * sizeof(int));

    char* line = malloc(100 * sizeof(char));

    char* name1 = malloc(20 * sizeof(char));
    char* name2 = malloc(20 * sizeof(char));
    int gain;
    char* gain_or_lose = malloc(20 * sizeof(char));

    while (getchar() != EOF) {
        fseek(stdin, -1, SEEK_CUR);

        fgets(line, 100, stdin);
        sscanf(line, "%s would %s %d happiness units by sitting next to %s.", name1, gain_or_lose, &gain, name2);

        graph[n_graph].name1 = name1[0];
        graph[n_graph].name2 = name2[0];

        graph[n_graph].happiness = (gain_or_lose[0] == 'g')?gain:-gain;

        add_name(names, &n_names, name1[0]);
        add_name(names, &n_names, name2[0]);

        n_graph++;
    }

    names[n_names] = 'i';
    n_names++;

    for (int i = 0; i < n_names; i++) {
        taken[i] = 0;
    }
    char* table = malloc(200 * sizeof(char));

    int total = compute_permutations(graph, n_graph, names, n_names, taken, table, 0);

    printf("%d\n", total);

    return 0;
}
