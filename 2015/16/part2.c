#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    CHILDREN,
    CATS,
    SAMOYEDS,
    POMERANIANS,
    AKITAS,
    VIZSLAS,
    GOLDFISH,
    TREES,
    CARS,
    PERFUMES
} element_t;

typedef struct {
    int children;
    int cats;
    int samoyeds;
    int pomeranians;
    int akitas;
    int vizslas;
    int goldfish;
    int trees;
    int cars;
    int perfumes;
} sue_t;

element_t str_to_element(char* str) {
    if (!strcmp(str, "children:")) {
        return CHILDREN;
    }
    if (!strcmp(str, "cats:")) {
        return CATS;
    }
    if (!strcmp(str, "samoyeds:")) {
        return SAMOYEDS;
    }
    if (!strcmp(str, "pomeranians:")) {
        return POMERANIANS;
    }
    if (!strcmp(str, "akitas:")) {
        return AKITAS;
    }
    if (!strcmp(str, "vizslas:")) {
        return VIZSLAS;
    }
    if (!strcmp(str, "goldfish:")) {
        return GOLDFISH;
    }
    if (!strcmp(str, "trees:")) {
        return TREES;
    }
    if (!strcmp(str, "cars:")) {
        return CARS;
    }
    if (!strcmp(str, "perfumes:")) {
        return PERFUMES;
    }
}

int sue_is_okay(sue_t data, element_t element, int n) {
    switch(element) {
        case CHILDREN:
            return data.children == n;
        case CATS:
            return data.cats < n;
        case SAMOYEDS:
            return data.samoyeds == n;
        case POMERANIANS:
            return data.pomeranians > n;
        case AKITAS:
            return data.akitas == n;
        case VIZSLAS:
            return data.vizslas == n;
        case GOLDFISH:
            return data.goldfish > n;
        case TREES:
            return data.trees < n;
        case CARS:
            return data.cars == n;
        case PERFUMES:
            return data.perfumes == n;
    }
}

int main() {
    sue_t sue_data;
    sue_data.children = 3;
    sue_data.cats = 7;
    sue_data.samoyeds = 2;
    sue_data.pomeranians = 3;
    sue_data.akitas = 0;
    sue_data.vizslas = 0;
    sue_data.goldfish = 5;
    sue_data.trees = 3;
    sue_data.cars = 2;
    sue_data.perfumes = 1;

    char* line = malloc(500 * sizeof(char));

    char** elements = malloc(3 * 20 * sizeof(char));
    elements[0] = malloc(20 * sizeof(char));
    elements[1] = malloc(20 * sizeof(char));
    elements[2] = malloc(20 * sizeof(char));

    int* elements_n = malloc(3 * sizeof(int));

    int n_sue;

    while (getchar() != EOF) {
        fseek(stdin, -1, SEEK_CUR);

        fgets(line, 500, stdin);

        sscanf(line, "Sue %d: %s %d, %s %d, %s %d\n", &n_sue, elements[0], &elements_n[0], elements[1], &elements_n[1], elements[2], &elements_n[2]);


        int is_sue = 1;

        for (int i = 0; i < 3; i++) {
            is_sue = is_sue && sue_is_okay(sue_data, str_to_element(elements[i]), elements_n[i]);
        }

        if (is_sue) {
            printf("%d\n", n_sue);
        }
    }
    return 0;
}

