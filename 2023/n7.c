#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct{
    int* cards_by_type;
    int* cards;
    int* sorted_cards_by_type;
    int type;
    int n_type;
    int bid;
} hand;


int cmp(hand* h1, hand* h2){
    if (h1->type < h2->type){
        return 1;
    }
    else if (h1->type > h2 ->type){
        return -1;
    }
    for (int i = 0; i < 5; i++){
        if (h1->cards[i] < h2->cards[i]){
            return 1;
        }
        else if (h1->cards[i] > h2->cards[i]){
            return -1;
        }
    }
    return 0;
}

int main(){
    hand** hands = malloc(2000 * sizeof(hand*));
    char c = getchar();
    int i = 0;
    int j;
    while(c != EOF){
        hands[i] = calloc(1, sizeof(hand));
        hands[i]->cards_by_type = calloc(15, sizeof(int));
        hands[i]->sorted_cards_by_type = calloc(10, sizeof(int));
        hands[i]->cards = calloc(10, sizeof(int));

        int n_card = 0;
        while (c != ' '){
            switch (c){
                case 'A': j = 0; break;
                case 'K': j = 1; break;
                case 'Q': j = 2; break;
                case 'T': j = 3; break;
                case 'J': j = 12; break;
                default : j = 13 - (int)(c -'0'); break;
            }
            hands[i]->cards_by_type[j]++;
            hands[i]->cards[n_card++] = j;
            c = getchar();
        }

        for (int k = 0; k < 12; k++){
            if(hands[i]->cards_by_type[k]){
                hands[i]->sorted_cards_by_type[hands[i]->n_type++] = hands[i]->cards_by_type[k];
            }
        }

        for (int k = 0; k < hands[i]->n_type; k++){
            for (int m = 0; m < hands[i]->n_type - k; m++){
                if (hands[i]->sorted_cards_by_type[m] < hands[i]->sorted_cards_by_type[m+1]){
                    int tmp = hands[i]->sorted_cards_by_type[m];
                    hands[i]->sorted_cards_by_type[m] = hands[i]->sorted_cards_by_type[m+1];
                    hands[i]->sorted_cards_by_type[m+1] = tmp;
                }
            }
        }

        hands[i]->sorted_cards_by_type[0] += hands[i]->cards_by_type[12];

        if (hands[i]->sorted_cards_by_type[0] == 5){
            hands[i]->type = 0;
        }
        else if (hands[i]->sorted_cards_by_type[0] == 4){
            hands[i]->type = 1;
        }
        else if (hands[i]->sorted_cards_by_type[0] == 3 && hands[i]->sorted_cards_by_type[1] == 2){
            hands[i]->type = 2;
        }
        else if (hands[i]->sorted_cards_by_type[0] == 3){
            hands[i]->type = 3;
        }
        else if (hands[i]->sorted_cards_by_type[0] == 2 && hands[i]->sorted_cards_by_type[1] == 2){
            hands[i]->type = 4;
        }
        else if (hands[i]->sorted_cards_by_type[0] == 2){
            hands[i]->type = 5;
        }
        else{
            hands[i]->type = 6;
        }
        
        scanf("%d\n", &hands[i]->bid);
        c = getchar();
        i++;
    }

    for (int k = 0; k < i; k ++){
        for (int j = 0; j < i - k - 1; j++){
            if (cmp(hands[j], hands[j+1]) > 0){
                hand* tmp = hands[j];
                hands[j] = hands[j+1];
                hands[j+1] = tmp;
            }
        }
    }



    int res = 0;
    for (int k = 0; k < i; k++){
        res += hands[k]->bid * (k+1);

    }
    printf("%d\n", res);
}