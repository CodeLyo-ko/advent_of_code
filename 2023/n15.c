#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char* label;
    int focal;
} Tpart;

void add_to_box(Tpart* box, int* n, Tpart e)
{
    for (int i = 0; i < (*n); i++)
    {
        if (!strcmp(box[i].label, e.label))
        {
            box[i] = e;
            return;
        }
    }
    box[*n] = e;
    (*n)++;

}

void remove_from_box(Tpart* box, int* n, Tpart e)
{
    int trouve = 0;
    for (int i = 0; i < (*n); i++)
    {
        if (!strcmp(box[i].label, e.label) || trouve)
        {
            box[i] = box[i+1];
            trouve = 1;
        }
    }
    if (trouve)
    (*n)--;
}

int main()
{
    Tpart** boxes = malloc(256 * sizeof(Tpart*));
    int* n = calloc(256, sizeof(int));

    for (int i = 0; i < 256; i++)
    {
        boxes[i] = malloc(100 * sizeof(Tpart));
    }



    char c = getchar();
    int res = 0;
    int hash;
    while ( c != EOF)
    {
        Tpart e;
        e.label = calloc(20, sizeof(char));
        hash = 0;
        while (c != ',' && c != '\n')
        {

            if (c == '=')
            {
                c = getchar();
                e.focal = c - '0';
                add_to_box(boxes[hash], &(n[hash]), e);
            }
            else if (c == '-')
            {
                remove_from_box(boxes[hash], &(n[hash]), e);
            }
            else 
            {
                hash += (c%256);
                hash *= 17;
                hash %= 256;
                e.label[strlen(e.label)] = c;
            }
            c = getchar();
        }

        c = getchar();
    }

    for (int i = 0; i < 256; i++)
    {
        for (int j = 0; j < n[i]; j++)
        {
            res += (i+1) * (j + 1) * boxes[i][j].focal; 
        }
    }
    printf("%d\n", res);
    return 0;
}