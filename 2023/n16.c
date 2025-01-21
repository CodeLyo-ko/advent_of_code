#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int x;
    int y;
    char direction; // 'n' = north, 'e' = east, 's' = south, 'w' = west
} Tbeam;

typedef struct
{
    char mirror;
    int visited;
    char* directions; //directions it has been visited from
} Tcase;

int inTab(char* T, char e, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (T[i] == e)
        {
            return 1;
        }
    }
    return 0;
}

int nbEnergized(Tcase** input, int n, int m, Tbeam* beams)
{
    int n_beams = 1;

    int appended;

    while (n_beams != 0)
    {
        for (int k = 0; k < n_beams; k++)
        {
            appended = 0;
            switch(input[beams[k].x][beams[k].y].mirror)
            {
                case '.':
                    switch(beams[k].direction)
                    {
                        case 'n':
                            beams[k].x--;
                            break;
                        case 'e':
                            beams[k].y++;
                            break;
                        case 's':
                            beams[k].x++;
                            break;
                        case 'w':
                            beams[k].y--;
                            break;
                    }
                    break;
                case '/':
                    switch(beams[k].direction)
                    {
                        case 'n':
                            beams[k].y++;
                            beams[k].direction = 'e';
                            break;
                        case 'e':
                            beams[k].x--;
                            beams[k].direction = 'n';
                            break;
                        case 's':
                            beams[k].y--;
                            beams[k].direction = 'w';
                            break;
                        case 'w':
                            beams[k].x++;
                            beams[k].direction = 's';
                            break;
                    }
                    break;
                case '\\':
                    switch(beams[k].direction)
                    {
                        case 'n':
                            beams[k].y--;
                            beams[k].direction = 'w';
                            break;
                        case 'e':
                            beams[k].x++;
                            beams[k].direction = 's';
                            break;
                        case 's':
                            beams[k].y++;
                            beams[k].direction = 'e';
                            break;
                        case 'w':
                            beams[k].x--;
                            beams[k].direction = 'n';
                            break;
                    }
                    break;
                case '-':
                    switch(beams[k].direction)
                    {
                        case 'n':
                            beams[k].y--;
                            beams[k].direction = 'w';

                            beams[n_beams].x = beams[k].x;
                            beams[n_beams].y = beams[k].y + 2;
                            beams[n_beams].direction = 'e';
                            n_beams++;
                            appended = 1;
                            break;
                        case 'e':
                            beams[k].y++;
                            break;
                        case 's':
                            beams[k].y--;
                            beams[k].direction = 'w';

                            beams[n_beams].x = beams[k].x;
                            beams[n_beams].y = beams[k].y + 2;
                            beams[n_beams].direction = 'e';
                            n_beams++;
                            appended = 1;
                            break;
                        case 'w':
                            beams[k].y--;
                            break;
                    }
                    break;
                case '|':
                    switch(beams[k].direction)
                    {
                        case 'n':
                            beams[k].x--;
                            break;
                        case 'e':
                            beams[k].x--;
                            beams[k].direction = 'n';

                            beams[n_beams].x = beams[k].x + 2;
                            beams[n_beams].y = beams[k].y;
                            beams[n_beams].direction = 's';
                            n_beams++;
                            appended = 1;
                            break;
                        case 's':
                            beams[k].x++;
                            break;
                        case 'w':
                            beams[k].x--;
                            beams[k].direction = 'n';

                            beams[n_beams].x = beams[k].x + 2;
                            beams[n_beams].y = beams[k].y;
                            beams[n_beams].direction = 's';
                            n_beams++;
                            appended = 1;
                            break;
                    }
                    break;
            }

            if(beams[k].x < 0 || beams[k].x > n - 1 || beams[k].y < 0 || beams[k].y > m - 1 || (input[beams[k].x][beams[k].y].visited && inTab(input[beams[k].x][beams[k].y].directions, beams[k].direction, input[beams[k].x][beams[k].y].visited)))
            {
                for (int i = k; i < n_beams - 1; i++)
                {
                    beams[i] = beams[i+1];
                }

                k--;
                n_beams--;
            }
            else
            {

                input[beams[k].x][beams[k].y].directions[input[beams[k].x][beams[k].y].visited++] = beams[k].direction;
            }

            if (appended)
            {
                if(beams[n_beams-1].x < 0 || beams[n_beams-1].x > n - 1 || beams[n_beams-1].y < 0 || beams[n_beams-1].y > m - 1 || (input[beams[n_beams-1].x][beams[n_beams-1].y].visited && inTab(input[beams[n_beams-1].x][beams[n_beams-1].y].directions, beams[n_beams-1].direction, input[beams[n_beams-1].x][beams[n_beams-1].y].visited)))
                {
                    n_beams--;
                }
                else
                {
                    
                    input[beams[n_beams-1].x][beams[n_beams-1].y].directions[input[beams[n_beams-1].x][beams[n_beams-1].y].visited++] = beams[n_beams-1].direction;
                }
            }

        }

    }

    int ans = 0;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (input[i][j].visited)
            {
                ans++;
                input[i][j].visited = 0; //init for next starter
            }
        }
    }

    return ans;

}

int main()
{
    Tcase** input = malloc(200 * sizeof(Tcase*));
    int n = 0;
    int m;
    char c = getchar();
    while (c != EOF)
    {
        m = 0;
        input[n] = calloc(200, sizeof(Tcase));
        while (c != '\n')
        {
            input[n][m].mirror = c;
            input[n][m++].directions = calloc(5, sizeof(char));
            c = getchar();
        }
        n++;
        c = getchar();
    }

    Tbeam* beams = malloc(200 * sizeof(Tbeam));
    int n_beams = 1;

    int max_ans = 0;
    int tmp;

    for (int i = 0; i < m; i++) //top row and down row
    {
        //top row
        beams[0].x = 0;
        beams[0].y = i;
        beams[0].direction = 's';

        input[0][i].visited = 1;
        input[0][i].directions[0] = 's';
        tmp = nbEnergized(input, n, m, beams);
        max_ans = (tmp > max_ans)?tmp:max_ans;

        //down row
        beams[0].x = n - 1;
        beams[0].y = i;
        beams[0].direction = 'n';

        input[n-1][i].visited = 1;
        input[n-1][i].directions[0] = 'n';
        tmp = nbEnergized(input, n, m, beams);
        max_ans = (tmp > max_ans)?tmp:max_ans;

    }

    for (int i = 0; i < n; i++) //left row and right row
    {
        //left row
        beams[0].x = i;
        beams[0].y = 0;
        beams[0].direction = 'e';

        input[i][0].visited = 1;
        input[i][0].directions[0] = 'e';
        tmp = nbEnergized(input, n, m, beams);
        max_ans = (tmp > max_ans)?tmp:max_ans;

        //down row
        beams[0].x = i;
        beams[0].y = m - 1;
        beams[0].direction = 'w';

        input[i][m-1].visited = 1;
        input[i][m-1].directions[0] = 'w';
        tmp = nbEnergized(input, n, m, beams);
        max_ans = (tmp > max_ans)?tmp:max_ans;

    }


    


    printf("%d\n", max_ans);
    return 0;
}