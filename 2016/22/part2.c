#include <stdio.h>
#include <stdlib.h>
#define MAX_ 100000

#define MAX_QUEUE 1000000

typedef struct {
    int x;
    int y;
    int size;
    int used;
    int avail;
    int usep;
} node_t;

void print_grid(node_t* nodes, int x, int y) {
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            node_t node = nodes[i * y + j];
            char c = '.';
            if (node.used == 0) c = '_';
            if (node.used > 100) c = '#';
            if (node.y == 0 && node.x == x - 1) c = 'G';
            if (node.x == 0 && node.y == 0) c = 'S';
            printf("%c", c);
        }
        printf("\n");
    }
}


int main() {
    node_t* nodes = malloc(MAX_ * sizeof(node_t));
    int n_node = 0;
    
    while(getchar() != EOF) {
        fseek(stdin, -1, SEEK_CUR);
        scanf("/dev/grid/node-x%d-y%d", &nodes[n_node].x, &nodes[n_node].y);
        scanf("%dT", &nodes[n_node].size);
        scanf("%dT", &nodes[n_node].used);
        scanf("%dT", &nodes[n_node].avail);
        scanf("%d%", &nodes[n_node].usep);
        getchar();
        getchar();
        n_node++;
    }

    int max_x = 0;
    int max_y = 0;
    int empty;
    for (int i = 0; i < n_node; i++) {
        if (nodes[i].x > max_x) {
            max_x = nodes[i].x;
        }
        if (nodes[i].y > max_y) {
            max_y = nodes[i].y;
        }
        if (nodes[i].used == 0) {
            empty = i;
        }

    }

    print_grid(nodes, max_x + 1, max_y + 1);

    printf("%d\n", nodes[empty].x + nodes[empty].y + max_x + 5 * (max_x - 1));
    return 0;
}
