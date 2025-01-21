#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct{
    int nb;
    int line;
    int row_deb;
    int row_end;
} num;

typedef struct{
    int line;
    int row;
    int n1;
    int n2;
    int n_num;
} charac;

int main(){
    char* buf = malloc(600 * sizeof(char));
    char** input = malloc(600 * 300 * sizeof(char));
    int n = 0;
    while(fgets(buf, 600, stdin) != NULL){
        input[n++] = strdup(buf);
    }
    int j;
    num** numbers = malloc(10000 * sizeof(num*));
    int n_num = 0;
    charac** symbole = malloc(10000 * sizeof(charac*));
    int n_sym = 0;

    int in_number;
    for (int i = 0; i < n; i++){
        j = 0;
        in_number = 0;

        while(input[i][j] != '\n' && input[i][j] != '\0'){
            if (isdigit(input[i][j])){
                if (!in_number){
                    numbers[n_num] = (num*)malloc(sizeof(num));
                    numbers[n_num]->nb = 0;
                    in_number = 1;
                    numbers[n_num]->line = i;
                    numbers[n_num]->row_deb = j;
                }
                numbers[n_num]->nb *= 10;
                numbers[n_num]->nb += input[i][j] - '0';
            }
            else{
                if (in_number){
                    in_number = 0;
                    numbers[n_num]->row_end = j - 1;
                    n_num++;
                }

                if (input[i][j] == '*'){
                    symbole[n_sym] = (charac*)calloc(1, sizeof(charac));
                    symbole[n_sym]->line = i;
                    symbole[n_sym]->row = j;
                    n_sym++;
                }

            }

            j++;
        }
        if (in_number){
            in_number = 0;
            numbers[n_num]->row_end = j - 1;
            n_num++;
        }
    }

    int line_deb, line_end, row_deb, row_end;
    int line, row;

    int res = 0;

    for (int j = 0; j < n_sym; j++){
        line = symbole[j]->line;
        row = symbole[j]->row;
        for (int i = 0; i < n_num; i++){
            line_deb = numbers[i]->line - 1;
            line_end = numbers[i]->line + 1;
            row_deb = numbers[i]->row_deb - 1;
            row_end = numbers[i]->row_end + 1;
            if (line >= line_deb && line <= line_end && row >= row_deb && row <= row_end){
                symbole[j]->n_num++;
                if (symbole[j]->n_num == 1){
                    symbole[j]->n1 = numbers[i]->nb;
                }
                else if (symbole[j]->n_num == 2){
                    symbole[j]->n2 = numbers[i]->nb;
                }
            }
        }
        if (symbole[j]->n_num == 2){
            res += (symbole[j]->n1 * symbole[j]->n2);
        }
    }

    printf("%d\n", res);
}