#include <stdio.h>
#include <stdlib.h>
#define MAX_ 10000

typedef struct {
    int x;
    int y;
    int size;
    int used;
    int avail;
    int usep;
} node_t;

int main() {
    node_t* nodes = malloc(MAX_ * sizeof(node_t));
    int n_node = 0;
    
    while(getchar() != EOF) {
        scanf("dev/grid/node-x%d-y%d %dT %dT %dT %d%\n", &nodes[n_node].x, &nodes[n_node].y, &nodes[n_node].size, &nodes[n_node].used, &nodes[n_node].avail, &nodes[n_node].usep);
        n_node++;
    }

    int res = 0;
    for (int i = 0; i < n_node; i++) {
        for (int j = 0; j < n_node; j++) {
            if (i == j) continue;
            if (nodes[i].used > 0 && nodes[i].used <= nodes[j].avail) {
                res++;
            }
        }
    }
    printf("%d\n", res);

    return 0;
}
