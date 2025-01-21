#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int i;
    int j;
} Tgalaxy;

typedef struct
{
    Tgalaxy* tab;
    int n;
} TtabGalaxy;

int abs(int n)
{
    return (n<0)?-n:n;
}

long Tgalaxy_distance(Tgalaxy g1, Tgalaxy g2)
{
    return abs(g1.i - g2.i) + abs(g1.j - g2.j);
}

int main()
{
    TtabGalaxy space;
    space.tab = malloc(500 * sizeof(Tgalaxy));
    space.n = 0;

    int* rowWithGalaxy = calloc(500, sizeof(int));
    int* columnWithGalaxy = calloc(500, sizeof(int));

    char c = getchar();
    int i = 0;
    int j;
    while (c != EOF)
    {
        j = 0;
        while (c  != '\n')
        {
            if (c == '#')
            {
                space.tab[space.n].i = i;
                space.tab[space.n++].j = j;

                rowWithGalaxy[i]++;
                columnWithGalaxy[j]++;
            }

            j++;
            c = getchar();
        }

        i++;
        c = getchar();
    }

    long ans = 0;
    long distance;
    int i_min, i_max, j_min, j_max;

    for (int i = 0; i < space.n - 1; i++)
    {
        for (int j = i + 1; j < space.n; j++)
        {
            distance = Tgalaxy_distance(space.tab[i], space.tab[j]);

            i_min = (space.tab[i].i < space.tab[j].i)?space.tab[i].i:space.tab[j].i;
            i_max = (space.tab[i].i > space.tab[j].i)?space.tab[i].i:space.tab[j].i;
            j_min = (space.tab[i].j < space.tab[j].j)?space.tab[i].j:space.tab[j].j;
            j_max = (space.tab[i].j > space.tab[j].j)?space.tab[i].j:space.tab[j].j;

            for (int k = i_min + 1; k < i_max; k++)
            {
                if(!rowWithGalaxy[k])
                {
                    distance += 1000000 - 1;
                }
            }

            for (int k = j_min + 1; k < j_max; k++)
            {
                if(!columnWithGalaxy[k])
                {
                    distance += 1000000 - 1;
                }
            }
            ans += distance;
        }

    }
    printf("%ld\n", ans);
    return 0;
}