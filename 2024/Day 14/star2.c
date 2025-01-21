#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct {
    int p_x, p_y, v_x, v_y;
} rob_t;

int is_robot(rob_t* robots, int n, int x, int y) {
    for (int i = 0; i < n; i++) {
        if(robots[i].p_x == x && robots[i].p_y == y) return 1;
    }
    return 0;
}

void print_robots(rob_t* robots, int n) {
    for (int i = 0; i < 101; i++) {
        for (int j = 0; j < 103; j++) {
            if (is_robot(robots, n, i, j))
                printf("8");
            else printf(".");
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    int x = 101;
    int y = 103;

    long q1 = 0;
    long q2 = 0;
    long q3 = 0;
    long q4 = 0;

    rob_t* robots = malloc(1500 * sizeof(rob_t));
    int n = 0;

    while(getchar() != EOF) {
        fseek(stdin, -1, SEEK_CUR);
        scanf("p=%d,%d v=%d,%d\n", &robots[n].p_x, &robots[n].p_y, &robots[n].v_x, &robots[n].v_y);
        n++;
    }

    for (int j = 1; j < 100000000; j++) {
    for (int i = 0; i < n; i++) {
        robots[i].p_x += robots[i].v_x;
        robots[i].p_y += robots[i].v_y;
        while (robots[i].p_x < 0)
            robots[i].p_x += x;
        while(robots[i].p_y < 0)
            robots[i].p_y += y;
        robots[i].p_x %= x;
        robots[i].p_y %= y;
    }

    for (int k = 1; k < x - 1; k++) {
        for (int l = 1; l < y - 1; l++) {
            if (is_robot(robots, n, k,l) && is_robot(robots, n, k-1,l) && is_robot(robots, n, k-1,l-1) && is_robot(robots, n, k,l-1) && is_robot(robots, n, k+1,l) && is_robot(robots, n, k,l+1) && is_robot(robots, n, k+1,l+1)) {
        print_robots(robots, n);
        printf("%d\n", j);

            }
        }
    }
    }
    return 0;
}
