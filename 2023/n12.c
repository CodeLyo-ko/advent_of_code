#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int* groups;
    int n_groups;
    char* machines;
    int n_machines;
} Trow;

long nbWays(char* machines, int n_machines, int i_machines, int* groups, int n_groups, int i_groups, int cur_group, long*** DP)
{
    long ans;

    if (i_machines == n_machines)
    {
        return (i_groups == n_groups && !cur_group) || (i_groups == n_groups - 1 && cur_group == groups[i_groups]);
        
    }
    else if (machines[i_machines] == '.')
    {
        ans = DP[i_machines][i_groups][cur_group];
        
        if (ans)
        {

            return (ans < 0)?0:ans;
        }

        if (cur_group)
        {
            if (cur_group == groups[i_groups])
            {
                ans = nbWays(machines, n_machines, i_machines + 1, groups, n_groups, i_groups + 1, 0, DP);
                DP[i_machines][i_groups][cur_group] = ((!ans)?-1:ans);
                
                return ans;
            }
            else 
            {
                DP[i_machines][i_groups][cur_group] = -1;
                return 0;
            }
            
        }
        ans = nbWays(machines, n_machines, i_machines + 1, groups, n_groups, i_groups, 0, DP);
        DP[i_machines][i_groups][cur_group] = ((!ans)?-1:ans);
        return ans;
    }
    else if (machines[i_machines] == '#')
    {
        if (i_groups >= n_groups)
        {
            return 0;
        }
        if (cur_group + 1 > groups[i_groups])
        {
            return 0;
        }
        return nbWays(machines, n_machines, i_machines + 1, groups, n_groups, i_groups, cur_group + 1, DP);
    }
    else
    {
        machines[i_machines] = '.';
        long tmp = nbWays(machines, n_machines, i_machines, groups, n_groups, i_groups, cur_group, DP);
        machines[i_machines] = '#';
        tmp +=  nbWays(machines, n_machines, i_machines, groups, n_groups, i_groups,cur_group, DP);
        machines[i_machines] = '?';
        return tmp;
    }
}

int main()
{
    Trow* input = malloc(1100 * sizeof(Trow));
    int n_row = 0;
    int i = 0;
    int j;

    char c = getchar();

    while (c != EOF)
    {
        input[i].groups = calloc(100, sizeof(int));
        input[i].n_groups = 0;
        input[i].machines = calloc(100, sizeof(char));
        input[i].n_machines = 0;

        j = 0;
        while( c != ' ')
        {
            input[i].machines[j] = c;
            j++;
            input[i].n_machines++;
            c = getchar();
        }

        j = 0;
        c = getchar();
        while(c != '\n')
        {
            
            if (c == ',')
            {
                j++;
                input[i].n_groups++;
            }
            else 
            {
                input[i].groups[j] *= 10;
                input[i].groups[j] += c - '0';
            }

            c = getchar();
            
        }
        input[i].n_groups++;
        i++;
        n_row++;
        c = getchar();
    }



    long ans = 0;
    for (int i = 0; i < n_row; i++)
    {
        char* str_tmp = strdup(input[i].machines);
        int* int_tmp = malloc(100 * sizeof(int));

        for (int j = 0; j < input[i].n_groups; j++)
        {
            int_tmp[j] = input[i].groups[j];
        }

        int n_tmp = input[i].n_groups;

        for (int j = 0; j < 4; j++)
        {
            input[i].machines[input[i].n_machines] = '?';
            strcat(input[i].machines, str_tmp);
            input[i].n_machines = strlen(input[i].machines);

            for (int k = 0; k < n_tmp; k++)
            {
                input[i].groups[input[i].n_groups] = int_tmp[k];
                input[i].n_groups++;
            }
                        
        }

        free (str_tmp); free(int_tmp);

        long*** DP = malloc((input[i].n_machines + 1) * sizeof(long**));
        for (int j = 0; j <= input[i].n_machines; j++)
        {
            DP[j] = malloc((input[i].n_groups + 1)* sizeof(long*));
            for (int k = 0; k <= input[i].n_groups; k++)
            {
                DP[j][k] = calloc(50, sizeof(long));
            }
        }
        
        

        long tmp = nbWays(input[i].machines, input[i].n_machines, 0, input[i].groups, input[i].n_groups, 0, 0, DP);
        
        for (int j = 0; j <= input[i].n_machines; j++)
        {
        
            for (int k = 0; k <= input[i].n_groups; k++)
            {
                free(DP[j][k]);
            }
            free(DP[j]);
        }
        free(DP);
        ans += tmp;
    }

    printf("%ld\n", ans);
    return 0;
}