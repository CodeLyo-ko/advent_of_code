#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
    long x;
    long y;
    long z;
} coord_t;

typedef struct
{
    coord_t position;
    coord_t velocity;
} hailstone_t;

void solve_linear(long double** matrix, int n)
//Gaussian elimination method

// result will be in the matrix
{

    long double ratio;

    /* [ ?? ?? ?? ?? | ?? ]
     * [ ?? ?? ?? ?? | ?? ]   
     * [ ?? ?? ?? ?? | ?? ]
     * [ ?? ?? ?? ?? | ?? ]
     */

    for (int k = 0; k < n - 1; k++)
    {
        for (int i = k + 1; i < n; i++)
        {
            ratio = matrix[i][k] / matrix[k][k];

            for (int j = 0; j <= n ; j++)
            {
                matrix[i][j] -= ratio * matrix[k][j];
                
            }
        }
    }

    
    /* [ ?? ?? ?? ?? | ?? ]
     * [ 00 ?? ?? ?? | ?? ]   
     * [ 00 00 ?? ?? | ?? ]
     * [ 00 00 00 ?? | ?? ]
     */


    for (int i = 0; i < n; i++)
    {
        ratio = matrix[i][i];

        for (int j = 0; j <= n ; j++)
        {
            matrix[i][j] /= ratio;
            
        }
    }

    
    /* [ 01 ?? ?? ?? | ?? ]
     * [ 00 01 ?? ?? | ?? ]   
     * [ 00 00 01 ?? | ?? ]
     * [ 00 00 00 01 | ?? ]
     */

    for (int k = n - 1; k > 0; k--)
    {
        for (int i = k - 1; i >= 0; i--)
        {
            ratio = matrix[i][k];

            for (int j = 0; j <= n ; j++)
            {
                matrix[i][j] -= ratio * matrix[k][j];
                
            }
        }
    }

    /* [ 01 00 00 00 | ?? ]
     * [ 00 01 00 00 | ?? ]   
     * [ 00 00 01 00 | ?? ]
     * [ 00 00 00 01 | ?? ]
     */
}

int main()
{
    hailstone_t* hailstones = malloc(300 * sizeof(hailstone_t));
    int n = 0;

    while (getchar() != EOF)
    {
        fseek(stdin, -1, SEEK_CUR);
        scanf("%ld, %ld, %ld @ %ld, %ld, %ld\n", &hailstones[n].position.x, &hailstones[n].position.y, &hailstones[n].position.z, &hailstones[n].velocity.x, &hailstones[n].velocity.y, &hailstones[n].velocity.z);
        n++;
    }

    long double** matrix = malloc(4 * sizeof(long double*));
    for (int i = 0; i < 4; i++)
    {
        matrix[i] = malloc(5 * sizeof(long double));
    }
    
    //we solve equation :
    // (dy1 - dy)X + (dx - dx1)Y + (y - y1)DX + (x1 - x)DY = x1 * dy1 - y1 * dx1 - x * dy + y * dx
    //here we get X, Y, DX, DY

    //and we solve the same equation by changing all the x or all the y to z, to get Z and DZ

    //x, y, z, dx, dy, dz are the coordinates of 1 random hailstones
    //x1, y1, z1, dx1, dy1, dz1 are the coordinates of different hailstones
    //we take 4 different x1 etc to get 4 equations, as we have 4 unkowns, to solve the equations

    long double X, Y, Z, DX, DY, DZ;

    long x, y, z, dx, dy, dz;
    x = hailstones[0].position.x;
    y = hailstones[0].position.y;
    z = hailstones[0].position.z;
    dx = hailstones[0].velocity.x;
    dy = hailstones[0].velocity.y;
    dz = hailstones[0].velocity.z;

    long x1, y1, z1, dx1, dy1, dz1;

    for (int i = 1; i <= 4; i++)
    //we fill the matrix
    {
        x1 = hailstones[i].position.x;
        y1 = hailstones[i].position.y;
        z1 = hailstones[i].position.z;
        dx1 = hailstones[i].velocity.x;
        dy1 = hailstones[i].velocity.y;
        dz1 = hailstones[i].velocity.z;

        matrix[i - 1][0] = dy1 - dy;
        matrix[i - 1][1] = dx - dx1;
        matrix[i - 1][2] = y - y1;
        matrix[i - 1][3] = x1 - x;
        matrix[i - 1][4] = x1 * dy1 - y1 * dx1 - x * dy + y * dx;
    }

    solve_linear(matrix, 4);  

    X = matrix[0][4];
    Y = matrix[1][4];
    DX = matrix[2][4];
    DY = matrix[3][4];

    for (int i = 1; i <= 4; i++)
    //we fill the matrix
    {
        x1 = hailstones[i].position.x;
        y1 = hailstones[i].position.y;
        z1 = hailstones[i].position.z;
        dx1 = hailstones[i].velocity.x;
        dy1 = hailstones[i].velocity.y;
        dz1 = hailstones[i].velocity.z;

        matrix[i - 1][0] = dy1 - dy;
        matrix[i - 1][1] = dz - dz1;
        matrix[i - 1][2] = y - y1;
        matrix[i - 1][3] = z1 - z;
        matrix[i - 1][4] = z1 * dy1 - y1 * dz1 - z * dy + y * dz;

    }

    solve_linear(matrix, 4);  

    Z = matrix[0][4];
    DZ = matrix[2][4];

    printf("(%Lf, %Lf, %Lf) (%Lf, %Lf, %Lf)\n", X, Y, Z, DX, DY, DZ);
    printf("%Lf\n", X + Y + Z); //take int value
    

    for (int i = 0; i < 4; i++)
    {
        free(matrix[i]);
    }
    free(matrix);

    free(hailstones);
    return 0;
}