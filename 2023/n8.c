#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct elm{
    char* val;
    char* L;
    char* R;
    struct elm* LP;
    struct elm* RP;
} Telm;

long gcd(long a, long b){
    long min = (a<b)?a:b;
    long max = (a>b)?a:b;
    if (!min){
        return max;
    }
    return (gcd(min, max%min));

}

long lcm(long a, long b){
    return ((a / gcd(a,b)) * b);
}

int main(){
    char* instrc = malloc(10000 * sizeof(char));
    int n_instrc = 0;
    int cur_instrc = 0;
    char c = getchar();
    while (c != '\n'){

        instrc[n_instrc] = c;
        n_instrc++;
        c = getchar();
    }

    getchar();

    Telm* map = malloc(1000 * sizeof(Telm));
    int n_map = 0;
    while (getchar() != EOF){
        fseek(stdin, -1, SEEK_CUR);
        map[n_map].LP = NULL;
        map[n_map].RP = NULL;
        map[n_map].val = malloc(10 * sizeof(char));
        map[n_map].L = malloc(10 * sizeof(char));
        map[n_map].R = malloc(10 * sizeof(char));
        c = getchar();
        int n = 0;
        while(c != ' '){
            map[n_map].val[n++] = c;
            c = getchar();
        }
        map[n_map].val[n] = '\0';
        getchar(); getchar(); getchar();
        c = getchar();
        n = 0;
        while(c != ','){
            map[n_map].L[n++] = c;
            c = getchar();
        }
        map[n_map].L[n] = '\0';
        getchar();
        c = getchar();
        n = 0;
        while(c != ')'){
            map[n_map].R[n++] = c;
            c = getchar();
        }
        map[n_map].R[n] = '\0';
        getchar();
        n_map++;
    }
    


    Telm** cur = malloc(100 * sizeof(Telm*));
    char** end = malloc(100 * 4 * sizeof(char));
    int n_cur = 0;
    int n_fin = 0;

    int** debToEnd = malloc(100 * sizeof(int*));
    int* cycle = calloc(100, sizeof(int));

    for (int i = 0; i < n_map; i++){
        if (map[i].val[2] == 'A'){
            cur[n_cur] = &map[i];
            debToEnd[n_cur++] = calloc(100, sizeof(int));
        }
        else if (map[i].val[2] == 'Z'){
            end[n_fin++] = map[i].val;
        }
    }

    int fin, res;

    for (int i = 0 ; i < n_cur; i++){
        fin = 0;
        res = 0;
        while (!fin){
            switch (instrc[cur_instrc]){
                case 'L': 
                    if(cur[i]->LP == NULL){
                        for (int j = 0; j < n_map; j++){
                            if (!strcmp(map[j].val, cur[i]->L)){
                                cur[i]->LP = &map[j];
                                break;
                            }
                        }    
                    }       

                    cur[i] = cur[i]->LP;
                    if (cur[i]->val[2] == 'Z'){
                        for (int k = 0; k < n_fin; k++){
                            if (!strcmp(end[k], cur[i]->val)){
                                if (debToEnd[i][k] == 0){
                                    debToEnd[i][k] = res;
                                }
                                else {
                                    cycle[i] = res - debToEnd[i][k];
                                    fin = 1;
                                }
                                break;
                            }
                        }
                    }

                    
                    res++;
                    cur_instrc++; cur_instrc %= n_instrc;
                    break;
                
                case 'R':
                    if(cur[i]->RP == NULL){
                        for (int j = 0; j < n_map; j++){
                            if (!strcmp(map[j].val, cur[i]->R)){
                                cur[i]->RP = &map[j];
                                break;
                            }
                        }    
                    }       

                    cur[i] = cur[i]->RP;
                    if (cur[i]->val[2] == 'Z'){
                        for (int k = 0; k < n_fin; k++){
                            if (!strcmp(end[k], cur[i]->val)){
                                if (debToEnd[i][k] == 0){
                                    debToEnd[i][k] = res;
                                }
                                else {
                                    cycle[i] = res - debToEnd[i][k];
                                    fin = 1;
                                }
                                break;
                            }
                        }
                    }

                    
                    res++;
                    cur_instrc++; cur_instrc %= n_instrc;
                    break;
            }

        
        }
    }

    for (int i = 0; i < n_cur; i++){
        for (int j = 0; j < n_fin; j++){
            printf("%d ", debToEnd[i][j]);
        }
        printf("|%d\n", cycle[i]);
    }


    long tmp = cycle[0];
    for (int i = 1; i < n_cur; i++){
        tmp = lcm(tmp, cycle[i]);
    }

    printf("%ld\n", tmp);

}