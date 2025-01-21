#include <stdio.h>
#include <stdlib.h>

int longest_path(char** grid, int n, int m, int x, int y, int prev_x, int prev_y)
{

    if (x == n - 1)
    //We arrived at the end
    {
        return 1;
    }

    int max = 0;
    int tmp;

    grid[x][y] = '#';

    if (x > 0 && grid[x - 1][y] != '#' && prev_x != x - 1 )
    {

        tmp = longest_path(grid, n, m, x - 1, y, x, y);
        grid[x - 1][y] = '.';

        if (tmp > max  && tmp != -1) max = tmp;
    }


    if (x < n - 1 && grid[x + 1][y] != '#' && prev_x != x + 1 )
    {
        tmp = longest_path(grid, n, m, x + 1, y, x, y);
        grid[x + 1][y] = '.';
        
        if (tmp > max  && tmp != -1) max = tmp;
    }


    if (y > 0 && grid[x][y - 1] != '#' && prev_y != y - 1 )
    {        
        tmp =  longest_path(grid, n, m, x, y - 1, x, y);
        grid[x][y - 1] = '.';
        
        if (tmp > max  && tmp != -1) max = tmp;
    }


    if (y < m - 1 && grid[x][y + 1] != '#' && prev_y != y + 1 )
    {
        tmp =  longest_path(grid, n, m, x, y + 1, x, y);
        grid[x][y + 1] = '.';

        if (tmp > max && tmp != -1) max = tmp;
    }

    if (max == 0) return -1;

    return max + 1;

}

int main()
{
    char** input = malloc(200 * sizeof(char*));
    int n = 0;
    int m;
    char c = getchar();

    while (c != EOF)
    {
        input[n] = calloc(200, sizeof(char));
        m = 0;
        while (c != '\n')
        {
            input[n][m++] = c;
            c = getchar();
        }
        n++;
        c = getchar();
    }

    int x = 0; int y = 1; //starting point
    

    printf("%d\n", longest_path(input, n, m, x, y, x, y) - 1);

    for (int i = 0; i < n; i++)
    {
        free(input[i]);
    }
    free(input);
    return 0;
}