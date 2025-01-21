#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int isMat(char** mat1, char** mat2, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (mat1[i][j] != mat2[i][j])
            {
                return 0;
            }
        }
    }
    return 1;
}

int inMat(char*** mat_mat, int n_mat_mat, char** mat, int n, int m)
{
    for (int k = 0; k < n_mat_mat; k++)
    {
        if (isMat(mat_mat[k], mat, n, m))
        {
            return k;
        }
    }
    return -1;
}

int main()
{
    char** mat = malloc(100 * sizeof(char*));
    int n = 0;
    int m;
    char c = getchar();
    while (c != EOF)
    {
        mat[n] = calloc(100, sizeof(char));
        m = 0;
        while (c != '\n')
        {
            mat[n][m++] = c;
            c = getchar();
        }
        n++;
        c = getchar();
    }

    int k;
    int nb_rock;

    char*** mat_mat = malloc(1000 * sizeof(char**));
    int n_mat_mat = 0;

    mat_mat[n_mat_mat] = malloc(100 * sizeof(char*));

    for (int i = 0; i < n; i++)
    {
        mat_mat[n_mat_mat][i] = calloc(100, sizeof(char));

        for (int j = 0; j < m; j++)
        {
            mat_mat[n_mat_mat][i][j] = mat[i][j];
        }
    }
    n_mat_mat++;

    int nb_cycle = -1;
    int cycle_actuel = 0;

    while (nb_cycle == -1)
    {
        cycle_actuel++;
        //north
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if ((!i && mat[i][j] != '#' )|| (i && mat[i-1][j] == '#' ))
                {
                    k = i; 
                    nb_rock = 0;
                    while (k < n && mat[k][j] != '#')
                    {
                    
                        if (mat[k][j] == 'O')
                        {
                            mat[k][j] = '.';
                            nb_rock++;
                        }
                        k++;
                    }

                    for (int p = i; p < i + nb_rock; p++)
                    {
                        mat[p][j] = 'O';
                    }

                }
            }
        }

        //west
        for (int j = 0; j < m; j++)
        {
            for (int i = 0; i < n; i++)
            {
                if ((!j && mat[i][j] != '#' )|| (j && mat[i][j-1] == '#' ))
                {
                    k = j; 
                    nb_rock = 0;
                    while (k < m && mat[i][k] != '#')
                    {
                    
                        if (mat[i][k] == 'O')
                        {
                            mat[i][k] = '.';
                            nb_rock++;
                        }
                        k++;
                    }

                    for (int p = j; p < j + nb_rock; p++)
                    {
                        mat[i][p] = 'O';
                    }

                }
            }
        }

        //south
        for (int i = n - 1; i >= 0; i--)
        {
            for (int j = 0; j < m; j++)
            {
                if ((i == n - 1 && mat[i][j] != '#' )|| (i < n - 1 && mat[i+1][j] == '#' ))
                {
                    k = i; 
                    nb_rock = 0;
                    while (k >= 0 && mat[k][j] != '#')
                    {
                    
                        if (mat[k][j] == 'O')
                        {
                            mat[k][j] = '.';
                            nb_rock++;
                        }
                        k--;
                    }

                    for (int p = i; p > i - nb_rock; p--)
                    {
                        mat[p][j] = 'O';
                    }

                }
            }
        }

        //east
        for (int j = m - 1; j >= 0; j--)
        {
            for (int i = 0; i < n; i++)
            {
                if ((j == m - 1 && mat[i][j] != '#' )|| (j < m - 1 && mat[i][j+1] == '#' ))
                {
                    k = j; 
                    nb_rock = 0;
                    while (k >= 0 && mat[i][k] != '#')
                    {
                    
                        if (mat[i][k] == 'O')
                        {
                            mat[i][k] = '.';
                            nb_rock++;
                        }
                        k--;
                    }

                    for (int p = j; p > j - nb_rock; p--)
                    {
                        mat[i][p] = 'O';
                    }

                }
            }
        }

        nb_cycle = inMat(mat_mat, n_mat_mat, mat, n, m);
        //printf("%d %d\n", nb_cycle, cycle_actuel);

        if (nb_cycle == -1)
        {
            mat_mat[n_mat_mat] = malloc(100 * sizeof(char*));

            for (int i = 0; i < n; i++)
            {
                mat_mat[n_mat_mat][i] = calloc(100, sizeof(char));

                for (int j = 0; j < m; j++)
                {
                    mat_mat[n_mat_mat][i][j] = mat[i][j];
                }
            }
            n_mat_mat++;
        }

    }

    mat = mat_mat[18+124]; //found with modulo

    int ans = 0;
    int lvl = n;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            
            ans += lvl * (mat[i][j] == 'O');
        }
        lvl--;
    }

    printf("%d %d %d\n", nb_cycle, cycle_actuel, ans);

    return 0;
}