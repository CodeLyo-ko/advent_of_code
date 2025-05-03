#include <stdio.h>
#include <stdlib.h>
#define MAX_BOT 500

typedef struct {
    int low;
    int high;
} rule_t;

typedef struct {
    int* chips;
    int n_chip;
} bot_t;

void run_simulation(rule_t* rules, bot_t* bots, int* outputs) {
    for (int i = 0; i < MAX_BOT; i++) {
        if (bots[i].n_chip == 2) {
            int low = bots[i].chips[0];
            int high = bots[i].chips[1];
            if (low > high) {
                int temp = low;
                low = high;
                high = temp;
            }

            bots[i].n_chip = 0;

            int b1 = rules[i].low;
            int b2 = rules[i].high;
            if (b1 >= 0) {
                bots[b1].chips[bots[b1].n_chip++] = low;
            }
            else {
                outputs[-b1 - 1] = low;
            }

            if (b2 >= 0) {
                bots[b2].chips[bots[b2].n_chip++] = high;
            }
            else {
                outputs[-b2 - 1] = high;
            }

            return run_simulation(rules, bots, outputs);
        }
    }
}


int main() {
    rule_t* rules = malloc(MAX_BOT * sizeof(rule_t)); 
    bot_t* bots = malloc(MAX_BOT * sizeof(bot_t));
    for (int i = 0; i < MAX_BOT; i++) {
        bots[i].n_chip = 0;
        bots[i].chips = malloc(2 * sizeof(int));
    }
    
    char* line = malloc(500 * sizeof(char));
    while (fgets(line, 500, stdin)) {
        if (line[0] == 'v') { //value goes to bot
            int value, bot;
            sscanf(line, "value %d goes to bot %d", &value, &bot);
            bots[bot].chips[bots[bot].n_chip++] = value;
        }
        else { //bot gives low to and high to
            int bot, n1, n2;
            char* w1 = malloc(10 * sizeof(w1));
            char* w2 = malloc(10 * sizeof(w2));
            sscanf(line, "bot %d gives low to %s %d and high to %s %d", &bot, w1, &n1, w2, &n2);
            rules[bot].low = (w1[0] == 'b') ? n1 : - n1 - 1;
            rules[bot].high = (w2[0] == 'b') ? n2 : - n2 - 1;
            free(w1); free(w2);
        }
    }
    
    int* outputs = calloc(MAX_BOT, sizeof(int));
    run_simulation(rules, bots, outputs);
    int result = 1;
    for (int i = 0; i < 3; i++) {
        result *= outputs[i];
    }

    printf("%d\n", result);
    return 0;
}
