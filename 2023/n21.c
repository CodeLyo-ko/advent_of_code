#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LENGTH 131

typedef struct
{
    int x;
    int y;
    int whole_x;
    int whole_y;
} coord_t;

typedef struct elm 
{
    coord_t* data;
    struct elm* next;
} elm_list_t;

typedef struct 
{
    elm_list_t* head;
    elm_list_t* tail;
    int num_elm;
} list_t;

void enfiler(list_t * l, int x, int y, int whole_x, int whole_y)
{
    elm_list_t* e = calloc(1, sizeof(elm_list_t));
    e->data =  malloc(1 * sizeof(coord_t));
    e->data->x = x;
    e->data->y = y;
    e->data->whole_x = whole_x;
    e->data->whole_y = whole_y;

    if (!l->num_elm)
    {
        l->head = e;
    }
    else
    {
        l->tail->next = e;
    }
    l->tail = e;
    l->num_elm++;
}

coord_t* defiler(list_t* l)
{
    elm_list_t* tmp = l->head;
    l->head = l->head->next;
    l->num_elm--;

    coord_t* dat = tmp->data;
    free(tmp);
    return dat;
}


int main()
{
    char** input = malloc(200 * sizeof(char*));

    int n = 0;
    int m;

    int start_x, start_y;
    
    char c = getchar();
    while(c != EOF)
    {
        input[n] = calloc(200, sizeof(char));
        m = 0;
        while(c != '\n')
        {
            input[n][m] = c;
            if (c == 'S')
            {
                start_x = n;
                start_y = m;
                input[n][m] = '.';
            }
            m++;
            c = getchar();
        }
        n++;
        c = getchar();
    }

    list_t* Lcases1 = calloc(1, sizeof(list_t));

    list_t* Lcases2 = calloc(1, sizeof(list_t));

    coord_t* coord;
    int x, y, whole_x, whole_y;

    int steps = 0;

    int max_steps = 0*LENGTH + LENGTH/2;
    //do it with 0, 1, 2 * length + length/2

    int max_size = (start_x + max_steps + 2) * 2;

    int** distances = malloc(max_size * sizeof(int*));
    for (int i = 0; i < max_size; i++)
    {
        distances[i] = malloc(max_size * sizeof(int));
        for (int j = 0; j < max_size; j++)
        {
            distances[i][j] = -1;
        }
    }

    enfiler(Lcases1, start_x, start_y, max_size/2, max_size/2);

    while (steps <= max_steps)
    {
        while (Lcases1->num_elm > 0)
        {
            coord = defiler(Lcases1);
            x = coord->x;
            y = coord->y;

            whole_x = coord->whole_x;
            whole_y = coord->whole_y;


            if (distances[whole_x][whole_y] != -1)
            {
                free(coord);
                continue;
            }
            distances[whole_x][whole_y] = steps;

            if (x <= 0)
            {
                x += n;
            }            
            if (input[x - 1][y] == '.' && distances[whole_x - 1][whole_y] == -1)
            {
                enfiler(Lcases2, x - 1, y, whole_x - 1, whole_y);
            }

            if (x >= n - 1)
            {
                x -= n;
            }

            if (input[x + 1][y] == '.' && distances[whole_x + 1][whole_y] == -1)
            {
                enfiler(Lcases2, x + 1, y, whole_x + 1, whole_y);
            }

            if (x < 0)
            {
                x += n;
            }   

            if (y <= 0)
            {
                y += m;
            }

            if (input[x][y - 1] == '.' && distances[whole_x][whole_y - 1] == -1)
            {
                enfiler(Lcases2, x, y - 1, whole_x, whole_y - 1);
            }

            if (y >= m - 1)
            {
                y -= m;
            }

            if (input[x][y + 1] == '.' && distances[whole_x][whole_y + 1] == -1)
            {
                enfiler(Lcases2, x, y + 1, whole_x, whole_y + 1);
            }

            free(coord);

        }
        steps++;
        while (Lcases2->num_elm > 0)
        {
            coord = defiler(Lcases2);
            enfiler(Lcases1, coord->x, coord->y, coord->whole_x, coord->whole_y);
            free(coord);
        }


    }
    
    int ans = 0;
    for (int i = 0; i < max_size; i++)
    {
        for (int j = 0; j < max_size; j++)
        {
            if (distances[i][j] == -1)
            {
                continue;
            }

            if (distances[i][j]%2 == max_steps%2)
            {
                ans++;
            }
        }
    }

    printf("%d\n", ans);

    //65 + 0 * 131 -> 3906
    //65 + 1 * 131 -> 34896
    //65 + 2 * 131 -> 96784
    // -> compute quadratic equation
    //solve with x = 202300 (bc nb of steps = 202300 * 131 + 65)

    //free
    for (int i = 0; i < max_size; i++)
    {
        free(distances[i]);
    }
    free(distances);

    elm_list_t* tmp = NULL;

    for (elm_list_t* e = Lcases1->head; e; e = e->next)
    {
        free(e->data);
        free(tmp);
        tmp = e;
    }
    free(Lcases1);

    for (elm_list_t* e = Lcases2->head; e; e = e->next)
    {
        free(e->data);
        free(tmp);
        tmp = e;
    }
    free(tmp);
    free(Lcases2);

    for (int i = 0; i < n; i++)
    {
        free(input[i]);
    }
    free(input);


    return 0;
}