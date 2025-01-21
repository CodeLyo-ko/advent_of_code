#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int vertical;
    int horizontal;
} Tdirection;

typedef struct 
{
    Tdirection d1;
    Tdirection d2;
    int isInLoop;
    char pipe;
} Tcase;

typedef struct 
{
    Tcase* tab;
    int n;
} TtabCase;

typedef struct 
{
    TtabCase* tab;
    int n;
} TmatCase;

int main()
{
    TmatCase* grid = malloc(sizeof(TmatCase));
    grid->n = 0;
    grid->tab = malloc(500 * sizeof(TtabCase));


    int i_start, j_start;
    int i = 0;
    char c = getchar();
    while (c != EOF)
    {
        grid->tab[grid->n].tab = malloc(1000 * sizeof(Tcase));
        grid->tab[grid->n].n = 0;
        int j = 0;
        while(c != '\n')
        {
            switch (c) 
            {
                case 'S' : i_start = i; j_start = j; break;

                case '7' : grid->tab[i].tab[j].d1.vertical = 0; grid->tab[i].tab[j].d1.horizontal = -1;
                    grid->tab[i].tab[j].d2.vertical = 1; grid->tab[i].tab[j].d2.horizontal = 0; break;

                case 'J' : grid->tab[i].tab[j].d1.vertical = -1; grid->tab[i].tab[j].d1.horizontal = 0;
                    grid->tab[i].tab[j].d2.vertical = 0; grid->tab[i].tab[j].d2.horizontal = -1; break;

                case 'L' : grid->tab[i].tab[j].d1.vertical = -1; grid->tab[i].tab[j].d1.horizontal = 0;
                    grid->tab[i].tab[j].d2.vertical = 0; grid->tab[i].tab[j].d2.horizontal = 1; break;

                case 'F' : grid->tab[i].tab[j].d1.vertical = 0; grid->tab[i].tab[j].d1.horizontal = 1;
                    grid->tab[i].tab[j].d2.vertical = 1; grid->tab[i].tab[j].d2.horizontal = 0; break;

                case '|' : grid->tab[i].tab[j].d1.vertical = -1; grid->tab[i].tab[j].d1.horizontal = 0;
                    grid->tab[i].tab[j].d2.vertical = 1; grid->tab[i].tab[j].d2.horizontal = 0; break;

                case '-' : grid->tab[i].tab[j].d1.vertical = 0; grid->tab[i].tab[j].d1.horizontal = -1;
                    grid->tab[i].tab[j].d2.vertical = 0; grid->tab[i].tab[j].d2.horizontal = 1; break;

                case '.' : grid->tab[i].tab[j].d1.vertical = 0; grid->tab[i].tab[j].d1.horizontal = 0;
                    grid->tab[i].tab[j].d2.vertical = 0; grid->tab[i].tab[j].d2.horizontal = 0; break;

            }
            grid->tab[i].tab[j].isInLoop = 0;
            grid->tab[i].tab[j].pipe = c;
            grid->tab[i].n++;
            j++;

            c = getchar();
        }

        i++;
        grid->n++;
        c = getchar();
    }
    
    int i_1, j_1, i_prev1, j_prev1;
    int i_2, j_2, i_prev2, j_prev2;

    int c1_trouve = 0;
    int north = 0; int south = 0; int west = 0; int east = 0;

    if (i_start > 0 && ( grid->tab[i_start-1].tab[j_start].d1.vertical == 1 || grid->tab[i_start-1].tab[j_start].d2.vertical == 1 ))
    //north of S
    {
        i_1 = i_start - 1;
        j_1 = j_start;
        c1_trouve = 1;
        north = 1;
    }
    if (i_start < grid->n - 1 && ( grid->tab[i_start+1].tab[j_start].d1.vertical == -1 || grid->tab[i_start+1].tab[j_start].d2.vertical == -1 ))
    //south of S
    {
        if (c1_trouve)
        {
            i_2 = i_start + 1;
            j_2 = j_start;
        }
        else
        {
            i_1 = i_start + 1;
            j_1 = j_start;
            c1_trouve = 1;
        }
        south = 1;
    }
    if (j_start > 0 && ( grid->tab[i_start].tab[j_start - 1].d1.horizontal == 1 || grid->tab[i_start].tab[j_start - 1].d2.horizontal == 1 ))
    //west of S
    {
        if (c1_trouve)
        {
            i_2 = i_start;
            j_2 = j_start - 1;
        }
        else
        {
            i_1 = i_start;
            j_1 = j_start - 1;
            c1_trouve = 1;
        }
        west = 1;
    }
    if (j_start < grid->n - 1 && ( grid->tab[i_start].tab[j_start + 1].d1.horizontal == -1 || grid->tab[i_start].tab[j_start + 1].d2.horizontal == -1 ))
    //east of S
    {
        i_2 = i_start;
        j_2 = j_start + 1;
        east = 1;

    }

    char pipe;
    if (north && south)
    {
        pipe = '|';
    }
    else if (north && east)
    {
        pipe = 'L';
    }
    else if (north && west)
    {
        pipe = 'J';
    }
    else if (east && west)
    {
        pipe = '-';
    }
    else if (east && south)
    {
        pipe = 'F';
    }
    else if (south && west)
    {
        pipe = '7';
    }

    grid->tab[i_start].tab[j_start].pipe = pipe;
    grid->tab[i_start].tab[j_start].isInLoop = 1;
    
    i_prev1 = i_start; i_prev2 = i_start;
    j_prev1 = j_start; j_prev2 = j_start;



    grid->tab[i_1].tab[j_1].isInLoop = 1;
    grid->tab[i_2].tab[j_2].isInLoop = 1;

    while(i_1 != i_2 || j_1 != j_2)
    {
        if (i_1 + grid->tab[i_1].tab[j_1].d1.vertical == i_prev1 && j_1 + grid->tab[i_1].tab[j_1].d1.horizontal == j_prev1)
        //we came from d1
        {
            i_prev1 = i_1; j_prev1 = j_1;
            i_1 += grid->tab[i_prev1].tab[j_prev1].d2.vertical;
            j_1 += grid->tab[i_prev1].tab[j_prev1].d2.horizontal;
        }
        else
        //we came from d2
        {
            i_prev1 = i_1; j_prev1 = j_1;
            i_1 += grid->tab[i_prev1].tab[j_prev1].d1.vertical;
            j_1 += grid->tab[i_prev1].tab[j_prev1].d1.horizontal;
        }

        if (i_2 + grid->tab[i_2].tab[j_2].d1.vertical == i_prev2 && j_2 + grid->tab[i_2].tab[j_2].d1.horizontal == j_prev2)
        //we came from d1
        {
            i_prev2 = i_2; j_prev2 = j_2;
            i_2 += grid->tab[i_prev2].tab[j_prev2].d2.vertical;
            j_2 += grid->tab[i_prev2].tab[j_prev2].d2.horizontal;
        }
        else
        //we came from d2
        {
            i_prev2 = i_2; j_prev2 = j_2;
            i_2 += grid->tab[i_prev2].tab[j_prev2].d1.vertical;
            j_2 += grid->tab[i_prev2].tab[j_prev2].d1.horizontal;
        }
        grid->tab[i_1].tab[j_1].isInLoop = 1;
        grid->tab[i_2].tab[j_2].isInLoop = 1;
    }

    int ans = 0;
    int inLoop;
    char pipe_deb;
    int isInLen;
    for (int i = 0; i < grid->n; i++)
    {
        inLoop = 0;
        isInLen = 0;
        for (int j = 0; j < grid->tab[i].n; j++)
        {
            if (grid->tab[i].tab[j].isInLoop)
            {
                if (isInLen)
                {
                    pipe = grid->tab[i].tab[j].pipe;
                    if (pipe != '-'){
                        if (pipe_deb == 'L' && pipe == '7' || pipe_deb == 'F' && pipe == 'J')
                        {
                            inLoop = !inLoop;
                        }
                        isInLen = 0;
                    }
                }
                else {
                    pipe = grid->tab[i].tab[j].pipe;
                    if (pipe == '|')
                    {
                        inLoop = !inLoop;
                    }
                    else
                    {
                        isInLen = 1;
                        pipe_deb = pipe;
                    }
                }
            }
            else 
            {
                if (inLoop)
                {
                    ans++;
                }
            }
        }
    }
    printf("%d\n", ans);


    return 0;
}