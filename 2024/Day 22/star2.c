#include <stdio.h>
#include <stdlib.h>

#define N_MAX 3000

typedef struct list_struct {
    int value;
    struct list_struct* next;
}   list_e_t;

typedef struct {
    list_e_t* first;
    list_e_t* last;
} list_t;

typedef struct {
    int sequence[4];
    int bananas[N_MAX];
} sequence_t;

long long generate_random (long long in) {
    long long out = in;
    long long temp;

    temp = 64 * out;
    out ^= temp;
    out %= 16777216;

    temp = out / 32;
    out ^= temp;
    out %= 16777216;

    temp = 2048 * out;
    out ^= temp;
    out %= 16777216;

    return out;
}

void add_sliding_window(list_t* sliding_window, int n, int k) {

    list_e_t* item = malloc(sizeof(list_e_t));
    item->value = n;
    item->next = NULL;

    if (!sliding_window->first) {
        sliding_window->first = item;
        sliding_window->last = item;
    }
    else if (k < 4) {
        sliding_window->last->next = item;
        sliding_window->last = item;
    }
    else {
        list_e_t* to_delete = sliding_window->first;
        sliding_window->first = sliding_window->first->next;
        sliding_window->last->next = item;
        sliding_window->last = item;
        free(to_delete);
    }
}

int tab_equal(int tab1[4], int tab2[4]) {
    for (int i = 0; i < 4; i++) {
        if (tab1[i] != tab2[i]) return 0;
    }
    return 1;
}

int in_sequence(sequence_t* sequences, int n_seq, int sequence[4]) {
    for (int i = 0; i < n_seq; i++) {
        if (tab_equal(sequences[i].sequence,sequence)){
            return i;
        }
    }

    return -1;
}

void reset_sliding_window(list_t* sliding_window) {
    list_e_t* temp;
    for (list_e_t* last = sliding_window->first; last != NULL; last = temp){
        temp = last->next;
        free(last);
    }

    sliding_window->first = NULL;
    sliding_window->last = NULL;
}

int sum_seq(int bananas[N_MAX]) {
    int total = 0;
    for (int i = 0; i < N_MAX; i++) {
        if (bananas[i] != -1) {
            total += bananas[i];
        }
    }
    return total;
}
int find_max_seq(sequence_t* sequences, int n_seq) {
    int max = 0;
    int temp;
    for (int i = 0; i < n_seq; i++) {
        temp = sum_seq(sequences[i].bananas);
        if (temp > max) {
            max = temp;
        }
    }

    return max;
}

void add_sequence(list_t* sliding_window, sequence_t* sequences, int* n_seq, int k, int bananas) {
    int seq[4];
    int i = 0;
    for( list_e_t* e = sliding_window->first; i < 4 ;e = e->next) {
        seq[i++] = e->value;
    }

    int k_seq;
    if ((k_seq = in_sequence(sequences, *n_seq, seq)) >= 0) {
        if(sequences[k_seq].bananas[k] == -1) {
            sequences[k_seq].bananas[k] = bananas;
        }
        return;
    }

    i = 0;
    for( list_e_t* e = sliding_window->first; i < 4 ;e = e->next) {
        sequences[*n_seq].sequence[i++] = e->value;
    }

    for (int i = 0; i < N_MAX; i++) {
        sequences[*n_seq].bananas[i] = -1;
    }

    sequences[*n_seq].bananas[k] = bananas;
    (*n_seq)++;
}

int main() {
    long long number;
    int k = 0;

    long long total = 0;

    sequence_t* sequences = malloc(19 * 19 * 19 * 19 * sizeof(sequence_t));
    int n_seq = 0;

    list_t* sliding_window = malloc(sizeof(list_t));
    sliding_window->first = NULL;
    sliding_window->last = NULL;

    int prev;
    int now, change;

    while (getchar() != EOF) {
        fseek(stdin, -1, SEEK_CUR);
        scanf("%lld\n", &number);
        prev = number%10;

        for (int i = 0; i < 2000; i++) {
            number = generate_random(number);
            now = number % 10;
            if (prev !=  -1) {
                change = now - prev;
                add_sliding_window(sliding_window, change, i);
            }
            // printf("%d\n", now);
            if (i >= 3) {
                add_sequence(sliding_window, sequences, &n_seq, k, now);
            }
            prev = now;
        }
        printf("%d\n", k);
        k++;
        reset_sliding_window(sliding_window);
    }

    total = find_max_seq(sequences, n_seq);

    printf("total : %lld\n", total);
    return 0;
}
