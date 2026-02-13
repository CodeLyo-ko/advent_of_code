#include <stdio.h>
#include <stdlib.h>
#define MAX_ 10000000

typedef struct ar {
    int id;
    struct ar* next;
    struct ar* prev;
} arr_t;

int main() {
    //example
    //int n_elves = 5;
    //input
    int n_elves = 3018458;

    arr_t* elf = malloc(sizeof(arr_t));
    elf->id = 1;

    arr_t* prev = elf;
    for (int i = 2; i <= n_elves; i++) {
        arr_t* temp = malloc(sizeof(arr_t));
        temp->id = i;
        temp->prev = prev;
        prev->next = temp;
        prev = temp;
    }

    prev->next = elf;
    elf->prev = prev;

    int n_pres = n_elves;
    int j = 0;
    arr_t* curr = elf;
    arr_t* halfway;
    arr_t* prev_r;
    arr_t* next_r;

    halfway = curr;
    j = n_pres / 2;
    for (int i = 0; i < j; i++) {
        halfway = halfway->next;
    }

    while (n_pres > 1) {
        prev_r = halfway->prev;
        next_r = halfway->next;

        prev_r->next = next_r;
        next_r->prev = prev_r;

        free(halfway);
        halfway = next_r;

        if (n_pres%2 == 1) {
            halfway = halfway->next;
        }
        curr = curr->next;
        n_pres--;
    }

    printf("%d\n", curr->prev->id);



    return 0;
}
