#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef enum {
    RSHIFT,
    OR,
    NOT,
    AND,
    LSHIFT,
    EMPTY,
    AND_1,
} gate_t;

typedef struct wire {
    gate_t gate;
    int shift;
    char* w1;
    char* w2;
    uint16_t val;
    int done;
    char* name;
} wire_t;

uint16_t to_int(char* word, int n) {
    uint16_t res = 0;

    int pow = 1;

    for (int i = n - 1; i >= 0; i--) {
        res += (word[i] - '0') * pow;
        pow *= 10;
    }
    return res;
}

gate_t to_gate(char* word, int n) {
    switch (word[0]) {
        case 'R':
            return RSHIFT;
        case 'O':
            return OR;
        case 'A':
            return AND;
        case 'N':
            return NOT;
        case 'L':
            return LSHIFT;
    }
    return EMPTY;
}

void split_input(char* line, gate_t* gate, int* shift, char* w1, char* w2, uint16_t* val, int* done, char* name) {
    *gate = EMPTY;
    *shift = -1;
    w1[0] = '\0';
    w2[0] = '\0';
    *val = 0;
    *done = 0;
    name[0] = '\0';


    char* word = malloc(20 * sizeof(char));
    int k = 0;
    int i = 0;
    while(line[i] != ' ') {
        word[k++] = line[i++];
    }

    word[k] = '\0';

    if (line[0] == '1' && line[2] == 'A') {
        *gate = AND_1;
        i = 6;
        k = 0;
        while(line[i] != ' ') {
            w1[k++] = line[i++];
        }
        w1[k] = '\0';

        i += 4;
        k = 0;
        while(line[i] != '\n') {
            name[k++] = line[i++];
        }
        name[k] = '\0';
        return;

    }
    if (word[0] >= '0' && word[0] <= '9') {
        *val = to_int(word, k);
        *done = 1;

        i += 4;

        k = 0;
        while(line[i] != '\n') {
            name[k++] = line[i++];
        }
        name[k] = '\0';
        return;
    }

    if (word[0] == 'N') {
        *gate = NOT;

        k = 0;
        i++;
        while(line[i] != ' ') {
            w1[k++] = line[i++];
        }
        w1[k] = '\0';

        i += 4;

        k = 0;
        while(line[i] != '\n') {
            name[k++] = line[i++];
        }
        name[k] = '\0';
        return;
    }

    k = 0;
    while(word[k] != '\0') {
        w1[k] = word[k];
        k++;
    }
    w1[k] = '\0';

    i++;
    k = 0;
    while(line[i] != ' ') {
        word[k++] = line[i++];
    }
    word[k] = '\0';

    *gate = to_gate(word, k);

    if (*gate == LSHIFT || *gate == RSHIFT) {
        i++;
        k = 0;
        while(line[i] != ' ') {
            word[k++] = line[i++];
        }
        word[k] = '\0';
        *shift = to_int(word, k);
    }
    else {
        k = 0;
        i++;
        while(line[i] != ' ') {
            w2[k++] = line[i++];
        }
        w2[k] = '\0';
    }

    i += 4;

    k = 0;
    while(line[i] != '\n') {
        name[k++] = line[i++];
    }
    name[k] = '\0';
    return;
}

void copy(char* s1, char* s2) {
    int i = 0;
    while (s1[i] != '\0') {
        s2[i] = s1[i];
        i++;
    }
    s2[i] = '\0';
}

wire_t new_wire(gate_t gate, int shift, char* w1, char* w2, uint16_t val, int done, char* name) {
    wire_t w;
    w.gate = gate;
    w.shift = shift;
    w.w1 = malloc(3 * sizeof(char));
    copy(w1, w.w1);
    w.w2 = malloc(3 * sizeof(char));
    copy(w2, w.w2);
    w.val = val;
    w.done = done;
    w.name = malloc(3 * sizeof(char));
    copy(name, w.name);
    return w;
}

int search_wire(wire_t* circuit, int n, char* name) {
    for (int i = 0; i < n; i++) {
        if (circuit[i].name[0] == name[0] && circuit[i].name[1] == name[1]) return i;
    }
}

uint16_t run(wire_t* circuit, int n, int current) {
    if (circuit[current].done) return circuit[current].val;

    uint16_t w1, w2;

    switch(circuit[current].gate) {
        case AND:
            w1 = run(circuit, n, search_wire(circuit, n, circuit[current].w1));
            w2 = run(circuit, n, search_wire(circuit, n, circuit[current].w2));
            circuit[current].val = w1 & w2;
            circuit[current].done = 1;
            break;

        case OR:
            w1 = run(circuit, n, search_wire(circuit, n, circuit[current].w1));
            w2 = run(circuit, n, search_wire(circuit, n, circuit[current].w2));
            circuit[current].val = w1 | w2;
            circuit[current].done = 1;
            break;

        case LSHIFT:
            w1 = run(circuit, n, search_wire(circuit, n, circuit[current].w1));
            circuit[current].val = w1 << circuit[current].shift;
            circuit[current].done = 1;
            break;

        case RSHIFT:
            w1 = run(circuit, n, search_wire(circuit, n, circuit[current].w1));
            circuit[current].val = w1 >> circuit[current].shift;
            circuit[current].done = 1;
            break;
        case NOT:
            w1 = run(circuit, n, search_wire(circuit, n, circuit[current].w1));
            circuit[current].val = ~w1;
            circuit[current].done = 1;
            break;
        case AND_1:
             w1 = run(circuit, n, search_wire(circuit, n, circuit[current].w1));
            circuit[current].val = 1 & w1;
            circuit[current].done = 1;
            break;
        case EMPTY:
            w1 = run(circuit, n, search_wire(circuit, n, circuit[current].w1));
            circuit[current].val = w1;
            circuit[current].done = 1;
            break;
    }

    return circuit[current].val;
}

int main() {
    wire_t* circuit = malloc(400 * sizeof(wire_t));
    int n = 0;

    char* line = malloc(50 * sizeof(char));
    gate_t gate;
    int shift;
    char* w1_name = malloc(3 * sizeof(char));
    char* w2_name = malloc(3 * sizeof(char));
    uint16_t val;
    int done;
    char* name = malloc(3 * sizeof(char));

    int n_a;

    while (getchar() != EOF) {
        fseek(stdin, -1, SEEK_CUR);
        fgets(line, 50, stdin);
        split_input(line, &gate, &shift, w1_name, w2_name, &val, &done, name);

        circuit[n] = new_wire(gate, shift, w1_name, w2_name, val, done, name);


        if (name[0] == 'a' && name[1] == '\0') n_a = n;
        n++;
    }

    run(circuit, n, n_a);

    printf("%d\n", circuit[n_a].val);
}
