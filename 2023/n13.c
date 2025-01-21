#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isSimmetryColumn(char** mat, int n, int m, int j)
{
    int j1 = j - 1;
    int j2 = j;

    int changed = 0;

    while(j1 >= 0 && j2 < m)
    {
        for (int i = 0; i < n; i++)
        {
            if (mat[i][j1] != mat[i][j2])
            {
                if (changed)
                {
                    return 0;
                }
                else
                {
                    changed = 1;
                }
            }
        }
        j1--; j2++;
    }
    return changed;
}

int findSimmetryColumn(char** mat, int n, int m)
{
    for (int j = 1; j < m; j++)
    {
        if (isSimmetryColumn(mat, n, m, j))
        {
            return j;
        }
    }
    return 0;
}

int isSimmetryRow(char** mat, int n, int m, int i)
{
    int i1 = i - 1;
    int i2 = i;

    int changed = 0;

    while(i1 >= 0 && i2 < n)
    {
        for (int j = 0; j < m; j++)
        {
            
            if (mat[i1][j] != mat[i2][j])
            {
                if (changed)
                {
                    return 0;
                }
                else 
                {
                    changed = 1;
                }
            }
        }
        i1--; i2++;
    }
    return changed;
}

int findSimmetryRow(char** mat, int n, int m)
{
    for (int i = 1; i < n; i++)
    {
        if (isSimmetryRow(mat, n, m, i))
        {
            return i;
        }
    }
    return 0;
}

int main()
{

    char** mat = malloc(100 * sizeof(char*));
    int n , m;
    char c = getchar();

    int simmetry, ans;
    ans = 0;
    while (c != EOF)
    {
        n = 0;

        while (c != '\n' && c != '\0' && c != EOF)
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
        c = getchar();

        simmetry = findSimmetryColumn(mat, n, m);
        if (simmetry)
        {
            ans += simmetry;
        }
        else 
        {
            simmetry = findSimmetryRow(mat, n, m);
            ans += 100 * simmetry;
        }
    }

    printf("%d\n", ans);
    return 0;
}