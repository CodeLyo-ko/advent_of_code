#include <stdio.h>
#include <stdlib.h>

typedef struct list {
    long value;
    struct list* suivant;
} list_t;

int digit(long l) {
    long n = l;
    int total = 0;
    do {
        n /= 10;
        total++;
    } while (n != 0);
    return total;
}

void add_list(list_t* l) {
    list_t* temp = malloc(sizeof(list_t));
    temp->value = 0;
    temp->suivant = l->suivant;
    l->suivant = temp;
}

void half_digit(list_t* l, list_t* l2, long n) {
    int ten_power = 1;

    l->value = 0;
    l2->value = 0;

    int d = digit(n);

    for (int i = 0; i < d / 2; i++) {
        l2->value += ten_power *(n%10) ;
        n /= 10;
        ten_power *= 10;
    }


    ten_power = 1;

    for (int i = 0; i < d / 2; i++) {
        l->value += ten_power * (n % 10);
        n /= 10;
        ten_power *= 10;
    }
}

int main() {
    int* input = malloc(100 * sizeof(int));
    int n = 0;

    while(getchar() != '\n') {
        fseek(stdin, -1, SEEK_CUR);
        scanf("%d", &input[n++]);
    }

    list_t* galets = malloc(sizeof(list_t));
    list_t* current = galets;

    for (int i = 0; i < n - 1; i++) {
        current->value = input[i];
        current->suivant = malloc(sizeof(list_t));
        current = current->suivant;
    }

    current->value = input[n - 1];
    current->suivant = NULL;



    for (int i = 0; i < 75; i++) {
        current = galets;
        while(current != NULL) {
            //printf("%d ", current->value);
            if (current->value == 0) {
                current->value = 1;
            }
            else if (digit(current->value) %2 == 0) {
                add_list(current);
                half_digit(current, current->suivant, current->value);
                current = current->suivant;

            }
            else {
                current->value *= 2024;
            }
            current = current->suivant;
        }
    }

    int total = 0;
    current = galets;
    while(current != NULL) {
        total++;
        current = current->suivant;
    }

    printf("%d\n", total);


    return 0;
}
