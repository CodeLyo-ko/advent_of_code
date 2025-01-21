#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char** str;
    int n;
} matrice;

int main(){
    FILE* f = fopen("input.txt", "r");

    matrice* m = malloc(sizeof(matrice));
    m->n = 0;
    m->str = malloc(200 * sizeof(char*));
    char* s = malloc(sizeof(char) * 500);
    

    while(fgets(s, 500, f)!= NULL){
        m->str[m->n++] = strdup(s);
    }

    char* j;
    int nb;
    char* color = malloc(sizeof(char) * 10);
    int n_c;
    int possible;

    int min_blue, min_red, min_green;

    int res = 0; 

    for (int i = 0; i < m->n; ++i){
        possible = 1;
        min_blue = 0; min_red = 0; min_green = 0;
        j = m->str[i];
        while(*j != ':'){
            j++;
        }
        j++;
        while (*j != '\0'){
            j++;
            nb = 0;
            while(*j != ' '){
                nb *= 10;
                nb += *j - '0';
                j++;

            }
            j++;
            n_c = 0;
            while(*j != ',' && *j != ';' && *j != '\0' && *j != '\n'){
                color[n_c] = *j;
                color[++n_c] = '\0';
                j++;
            }
            if (*j != '\0'){
                j++;
            }

            if (!strcmp(color, "blue")){
                min_blue = (nb > min_blue)?nb:min_blue;
            }
            if (!strcmp(color, "green")){
                min_green = (nb > min_green)?nb:min_green;
            }
            if (!strcmp(color, "red")){
                min_red = (nb > min_red)?nb:min_red;
            }
        }
        res += (min_red * min_blue * min_green);
        
    }
    printf("%d\n", res);

    fclose(f);
}