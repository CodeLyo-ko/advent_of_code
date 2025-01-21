#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} coord_t;

int in_tab(coord_t* tab, int n, int x, int y) {
    for (int i = 0; i < n; i++) {
        if (tab[i].x == x && tab[i].y == y) return 1;
    }
    return 0;
}

void add_coord(coord_t* houses_list, int* n, int x, int y) {
    if (in_tab(houses_list, *n, x, y)) return;

    houses_list[*n].x = x;
    houses_list[*n].y = y;
    (*n)++;
}

int main() {
    coord_t* houses_list = malloc(200 * 200 * sizeof(coord_t));
    int n_houses = 0;

    int x = 0;
    int y = 0;

    add_coord(houses_list, &n_houses,  x, y);

    char dep;

    while((dep = getchar()) != '\n') {
        switch (dep) {
            case '>':
                x++;
                break;
            case '<':
                x--;
                break;
            case '^':
                y--;
                break;
            case 'v':
                y++;
                break;
        }
        add_coord(houses_list, &n_houses, x, y);
    }

    printf("%d\n",  n_houses);
}
