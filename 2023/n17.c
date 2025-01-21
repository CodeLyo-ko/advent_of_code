#include <stdio.h>
#include <stdlib.h>

typedef enum { X, Y} Tdir;

typedef struct elm
{
    int x;
    int y;
    Tdir dir;
    struct elm* next;
}  Telm;

typedef struct
{
    Telm* head;
    Telm* tail;
    int numelm;
} Tlist;

void enfiler(Tlist* l, int x, int y, Tdir dir)
{
    Telm* e = calloc(1, sizeof(Telm));
    e->x = x;
    e->y = y;
    e->dir = dir;

    if (!l->numelm)
    {
        l->head = e;
    }
    else
    {
        l->tail->next = e;
    }
    l->tail = e;
    l->numelm++;
}

Telm* defiler(Tlist* l)
{
    Telm* tmp = l->head;
    l->head = l->head->next;
    l->numelm--;
    return tmp;
}


int main()
{
    int** input = malloc(200 * sizeof(int*));
    int n = 0;
    int m;
    char c = getchar();
    while (c != EOF)
    {
        m = 0;
        input[n] = calloc(200, sizeof(int));
        while (c != '\n')
        {
            input[n][m++] = c - '0';
            c = getchar();
        }
        n++;
        c = getchar();
    }

    int*** DP = malloc(n * sizeof(int**));
    for (int i = 0; i < n; i++)
    {
        DP[i] = malloc(m * sizeof(int*));
        for (int j = 0; j < m; j++)
        {
            DP[i][j] = malloc(2 * sizeof (int));
            DP[i][j][0] = m * n * 10;
            DP[i][j][1] = m * n * 10;
        }
    }

    DP[0][0][0] = 0;
    DP[0][0][1] = 0;

    Tlist* L = calloc(1, sizeof(Tlist));

    enfiler(L, 0, 0, X); enfiler(L, 0, 0, Y);

    int x, y, sumHeat;
    Tdir dir;
    Telm* e;

    while(L->numelm != 0)
    {
        e = defiler(L);
        x = e->x;
        y = e->y;
        dir = e->dir;
        free(e);

        if (dir == X)
        {
            sumHeat = DP[x][y][X];
            for (int i = 1; i <= 3; i++)
            {
                if (x + i < n)
                {
                    sumHeat += input[x + i][y];
                    if (sumHeat < DP[x + i][y][Y])
                    {
                        DP[x + i][y][Y] = sumHeat;
                        enfiler(L, x + i, y, Y);
                    }
                }
            }

            sumHeat = DP[x][y][X];
            for (int i = 1; i <= 3; i++)
            {
                if (x - i >= 0)
                {
                    sumHeat += input[x - i][y];
                    if (sumHeat < DP[x - i][y][Y])
                    {
                        DP[x - i][y][Y] = sumHeat;
                        enfiler(L, x - i, y, Y);
                    }
                }
            }
        }

        if (dir == Y)
        {
            sumHeat = DP[x][y][Y];
            for (int i = 1; i <= 3; i++)
            {
                if (y + i < m)
                {
                    sumHeat += input[x][y + i];
                    if (sumHeat < DP[x][y + i][X])
                    {
                        DP[x][y + i][X] = sumHeat;
                        enfiler(L, x, y + i, X);
                    }
                }
            }

            sumHeat = DP[x][y][Y];
            for (int i = 1; i <= 3; i++)
            {
                if (y - i >= 0)
                {
                    sumHeat += input[x][y - i];
                    if (sumHeat < DP[x][y - i][X])
                    {
                        DP[x][y - i][X] = sumHeat;
                        enfiler(L, x, y - i, X);
                    }
                }
            }
        }
    }
    

    printf("%d %d\n", DP[n - 1][m -1][X], DP[n - 1][m - 1][Y]); //take min between the 2
    return 0;
}