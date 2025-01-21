#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define abs(a) ((a) < 0)?-(a):a

typedef enum { R, D, L, U} Tdir;

typedef struct
{
    char dir;
    long nb;
    char* color;
} Tdig;

typedef struct
{
    long x;
    long y;
} Tvertex;

int main()
{
    Tdig* input = malloc(700 * sizeof(Tdig));
    int n_input = 0;
    char c = getchar();
    while (c != EOF)
    {
        while (c != '#')
        {
            c = getchar();
        }
        c = getchar();

        input[n_input].color = calloc(5, sizeof(char));
        int m = 0;

        while (c != ')')
        {
            input[n_input].color[m++] = c;
            c = getchar();
        }
        input[n_input].dir = input[n_input].color[m - 1] - '0';
        input[n_input].color[m-1] = '\0';
        n_input++;
        c = getchar(); c = getchar();
    }

    
    for (int i = 0; i < n_input; i++)
    {
        input[i].nb = strtol(input[i].color, NULL, 16);
    }

    

    long x = 0; long y = 0;

    Tvertex* vertices = malloc((n_input + 1) * sizeof(Tvertex));
    int n_vertex = 0;    
    vertices[n_vertex].x = x;
    vertices[n_vertex].y = y;
    n_vertex++;

    for (int i = 0; i < n_input; i++)
    {
        switch (input[i].dir)
        {
            case R:
                y += input[i].nb ;
                break;
            case L:
                y -= input[i].nb;
                break;
            case U:
                x -= input[i].nb;
                break;
            case D:
                x += input[i].nb;
                break;
        }

        vertices[n_vertex].x = x;
        vertices[n_vertex].y = y;
        n_vertex++;
    }

    long ans = 0;

    for (int i = 0; i < n_vertex - 1; i++)
    {
        ans += vertices[i + 1].x * vertices[i].y - vertices[i + 1].y * vertices[i].x;
        
    }    


    long peri = 0;

    for (int i = 0; i < n_vertex - 1; i++)
    {
        peri += abs(vertices[i].x - vertices[i+1].x + vertices[i].y - vertices[i+1].y);
        
    } 


    printf("%ld\n", ans/2 + peri/2 + 1);
    return 0;
}