#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(){
    long time = 0;
    char c = getchar();
    while(c != '\n'){
        if (isdigit(c)){
            time *= 10;
            time += c - '0';
        }
        c = getchar();
    }

    long int distance = 0;
    c = getchar();
    while(c != '\n'){
        if (isdigit(c)){
            distance *= 10;
            distance += c - '0';
        }
        c = getchar();
    }
    int res = 1;
    int cmpt;

    cmpt = 0;
    for (int j = 0; j <= time; j++){
        if (j * (time - j) > distance){
            cmpt++;
        }
    }
    printf("%d\n",cmpt);
}