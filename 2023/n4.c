#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

int main(){
    char* buf = malloc(sizeof(char) * 500);
    char** input = malloc(sizeof(char) * 500 * 200);
    int n = 0;
    while(fgets(buf, 500, stdin) != NULL){
        input[n++] = strdup(buf);
    }
    
    int j;

    int* winning = malloc(sizeof(int) * 100);
    int n_win;

    int* my_num = malloc(sizeof(int) * 100);
    int n_mine;

    int point;

    int* scratchcards = calloc(200, sizeof(int));

    int res = 0;

    for (int i = 0; i < n; i++){
        j = 0;
        while(input[i][j] != ':'){
            j++;
        }
        j += 2;

        n_win = 0;

        while(input[i][j] != '|'){
            winning[n_win] = 0;
            while(input[i][j] != ' '){
                winning[n_win] *= 10;
                winning[n_win] += input[i][j] - '0';
                j++;
                
            }
            if(input[i][j-1] != ' '){
                n_win++;    
            }
            j++;
        }
        
        j += 2;
        n_mine = 0;
        while(input[i][j] != '\n' && input[i][j] != '\0'){
            my_num[n_mine] = 0;
            while(input[i][j] != ' ' && input[i][j] != '\n'){
                my_num[n_mine] *= 10;
                my_num[n_mine] += input[i][j] - '0';
                j++;
            }
            if(input[i][j-1] != ' '){
                n_mine++;    
            }
            j++;
        }

        point = 0;
        for (int k = 0; k < n_mine; k++){
            for (int l = 0; l < n_win; l++){
                if (my_num[k] == winning[l]){
                    point++;
                    
                    break;
                }
            }
        }

        scratchcards[i]++;
        
        for (int m = i + 1; m <= point + i; m++){
            scratchcards[m] += scratchcards[i];
        }
        res += scratchcards[i];
    }
    printf("%d", res);
}
