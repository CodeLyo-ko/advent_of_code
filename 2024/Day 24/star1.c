#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    char wire[4];
    int bit;
} wire_t;

typedef struct {
    int wire1;
    int wire2;
    int wire3;
    char gate;
    int done;
} gate_t;

int search (wire_t* wires, int* n_wire, char wire[4]) {
    for (int i = 0; i < *n_wire; i++) {
        if (wires[i].wire[0] == wire[0] && wires[i].wire[1] == wire[1] && wires[i].wire[2] == wire[2]) {
            return i;
        }
    }

    wires[*n_wire].wire[0] = wire[0];
    wires[*n_wire].wire[1] = wire[1];
    wires[*n_wire].wire[2] = wire[2];
    wires[*n_wire].bit = -1;
    (*n_wire)++;
    return (*n_wire) - 1;
}

int main() {
    wire_t* wires = malloc(300 * 3 * sizeof(wire_t));
    int n_wires = 0;


    while (getchar() != '-'){
        fseek(stdin, -1, SEEK_CUR);
        scanf("%c%c%c: %d\n", &wires[n_wires].wire[0], &wires[n_wires].wire[1], &wires[n_wires].wire[2], &wires[n_wires].bit);
        n_wires++;
    }

    gate_t* gates = malloc(300 * sizeof(gate_t));
    int n_gates = 0;

    char wire1[4], wire2[4], wire3[4], gate[4];
    while(getchar() != EOF) {
        fseek(stdin, -1, SEEK_CUR);
        scanf("%s %s %s -> %s\n", wire1, gate, wire2, wire3);
        gates[n_gates].done = 0;
        gates[n_gates].wire1 = search(wires, &n_wires, wire1);
        gates[n_gates].wire2 = search(wires, &n_wires, wire2);
        gates[n_gates].wire3 = search(wires, &n_wires, wire3);
        gates[n_gates].gate = gate[0];
        n_gates++;
    }

    int stop = 0;
    int w1, w2, w3;

    while(!stop) {
        stop = 1;
        for (int i = 0; i < n_gates; i++) {
            if (gates[i].done) {
                continue;
            }

            w1 = gates[i].wire1;
            w2 = gates[i].wire2;
            w3 = gates[i].wire3;

            if (wires[w1].bit != -1 && wires[w2].bit != -1) {
                switch (gates[i].gate) {
                    case ('X') :
                        wires[w3].bit = wires[w1].bit ^ wires[w2].bit;
                        break;
                    case ('A') :
                        wires[w3].bit = wires[w1].bit & wires[w2].bit;
                        break;
                    case ('O') :
                        wires[w3].bit = wires[w1].bit | wires[w2].bit;
                        break;
                }

                gates[i].done = 1;
                stop = 0;
            }
        }
    }

    long long z = 0;
    int n;

    for(int i = 0; i < n_wires; i++) {
        if (wires[i].wire[0] == 'z' && wires[i].bit) {
            n = (wires[i].wire[1] - '0') * 10 + (wires[i].wire[2] - '0');
            z += pow(2, n);
        }
    }

    printf("%lld\n", z);
    return 0;
}
