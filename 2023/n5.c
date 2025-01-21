#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct{
    long long dest;
    long long src;
    long long range;
} convert;

int main(){
    char* buf = malloc(500 * sizeof(char));
    fgets(buf, 500, stdin);
    int i = 0;
    while (buf[i] != ':'){
        i++;
    }
    i++;

    long long* seeds = calloc(100000, sizeof(long long));
    int n_seed = 0;

    while (buf[i] != '\n' && buf[i] != '\0'){
        i++;
        while (buf[i] != ' ' && buf[i] != '\n'){
            seeds[n_seed] *= 10;
            seeds[n_seed] += buf[i] - '0';
            i++;
        }
        n_seed++;
    }

    getchar();

    convert** map = malloc(200 * sizeof(convert*));
    long long src, dest, range;
    
    while(getchar() != EOF){
        fseek(stdin, -1, SEEK_CUR);
        fgets(buf, 500, stdin);
        int n_map = 0;

        while(isdigit(getchar())){
            fseek(stdin, -1, SEEK_CUR);
            map[n_map] = malloc(sizeof(convert));
            fscanf(stdin, "%lld %lld %lld\n", &(map[n_map]->dest), &(map[n_map]->src), &(map[n_map]->range));
            n_map++;
        }

        for (int i = 0; i < n_seed; i+=2){
            for (int j = 0; j < n_map; j++){
                src = map[j]->src;
                dest = map[j]->dest;
                range = map[j]->range;

                if (seeds[i] >= src && seeds[i] + seeds[i+1] < src + range){ //intervalle inclut
                    seeds[i] += dest - src;
                    break;
                }
                else if (seeds[i] >= src && seeds[i] < src + range){ //début d'intervalle inclut
                    seeds[n_seed + 1] = seeds[i+1] + seeds[i] - (src + range);
                    seeds[n_seed] = src + range;
                    n_seed += 2;
                    seeds[i+1] = range + src - seeds[i];
                    seeds[i] += dest - src;
                    break;
                }
                else if (seeds[i] + seeds[i+1] - 1 >= src && seeds[i] + seeds[i+1] < src + range){ //fin d'intervalle inclut
                    seeds[n_seed] = seeds[i];
                    seeds[n_seed + 1] = src - seeds[i];
                    n_seed += 2;
                    seeds[i] = dest;
                    seeds[i+1] -= seeds[n_seed - 1];
                    break;
                }
                else if (seeds[i] < src && seeds[i] + seeds[i+1] >= src + range){ //milieu d'invervalle inclut
                    seeds[n_seed] = seeds[i];
                    seeds[n_seed + 1] = src - seeds[i];
                    n_seed += 2;
                    seeds[n_seed] = src + range;
                    seeds[n_seed + 1] = seeds[i+1] + seeds[i] - (src + range);
                    n_seed += 2;

                    seeds[i] = dest;
                    seeds[i+1] = range;
                    break;
                }

            }
        }
    }

    long long res = seeds[0];
    for (int i = 2; i < n_seed; i+=2){
        res = (seeds[i] < res)?seeds[i]:res;
    }

    printf("%lld\n", res);

}