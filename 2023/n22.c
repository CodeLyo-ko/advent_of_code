#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int x;
    int y;
    int z;
} coord_t;

typedef struct 
{
    coord_t end1;
    coord_t end2;
} brick_t;

int cmp_bricks(const void* e1, const void* e2)
{
    const brick_t* brick1 = e1;
    const brick_t* brick2 = e2;
    return (brick1->end2.z - brick2->end2.z);
}

int isBelow(brick_t brick1, brick_t brick2)
{
    return ((brick1.end1.x <= brick2.end2.x && brick1.end2.x >= brick2.end1.x) && (brick1.end1.y <= brick2.end2.y && brick1.end2.y >= brick2.end1.y) && (brick1.end2.z < brick2.end1.z));
}

int isSupporting(brick_t brick1, brick_t brick2)
{
    return ((brick1.end1.x <= brick2.end2.x && brick1.end2.x >= brick2.end1.x) && (brick1.end1.y <= brick2.end2.y && brick1.end2.y >= brick2.end1.y) && (brick1.end2.z == brick2.end1.z - 1));
}

int make_brick_fall(brick_t* bricks, int n_bricks, brick_t* brick, int i_brick)
//return 1 if brick moved, 0 if stayed where it was
{
    int max_z = 0;
    for (int i = i_brick - 1; i >= 0; i--)
    {
        if(bricks[i].end2.z >= brick->end1.z)
        {
            continue;
        }

        if (isBelow(bricks[i], *brick) && bricks[i].end2.z > max_z)
        {
            max_z = bricks[i].end2.z;
            break;
        }
    }

    max_z++;
    int diffZ = brick->end1.z - max_z;

    brick->end1.z -= diffZ;
    brick->end2.z -= diffZ;

    return diffZ;
}

int make_all_bricks_fall(brick_t* bricks, int n_bricks)
{
    int nb_bricks_fell = 0;
    for (int i = 0; i < n_bricks; i++)
    {
        if (make_brick_fall(bricks, n_bricks, &(bricks[i]), i))
        {
            qsort(bricks, n_bricks, sizeof(brick_t), cmp_bricks);
            nb_bricks_fell++;
        }
    }
    return nb_bricks_fell;
}

brick_t* duplicate_bricks_sub_one(brick_t* bricks, int n_bricks, int index)
{
    brick_t* bricks_dup = malloc(n_bricks * sizeof(brick_t));
    int n_bricks_dup = 0;

    for (int i = 0; i < n_bricks; i++)
    {
        if (i != index)
        {
            bricks_dup[n_bricks_dup++] = bricks[i];
        }
    }

    return bricks_dup;
}

int main()
{
    brick_t* bricks = malloc(2000 * sizeof(brick_t));
    int n_bricks = 0;

    while(getchar() != EOF)
    {
        fseek(stdin, -1, SEEK_CUR);
        scanf("%d,%d,%d~%d,%d,%d\n", &bricks[n_bricks].end1.x, &bricks[n_bricks].end1.y, &bricks[n_bricks].end1.z, &bricks[n_bricks].end2.x, &bricks[n_bricks].end2.y, &bricks[n_bricks].end2.z);
        n_bricks++;
    }

    qsort(bricks, n_bricks, sizeof(brick_t), cmp_bricks);

    make_all_bricks_fall(bricks, n_bricks);

    brick_t* dup_bricks;
    
    int ans = 0;

    for (int i = 0; i < n_bricks; i++)
    {
       dup_bricks = duplicate_bricks_sub_one(bricks, n_bricks, i);
       ans += make_all_bricks_fall(dup_bricks, n_bricks - 1);
       free(dup_bricks);
    }


    printf("%d\n", ans);


    free(bricks);

    return 0;
}