#include <stdio.h>
#include <stdlib.h>

#define ON '#'
#define OFF '.'

int n_neighbours(char** grid, int i, int j, int n) {
	int neighbours = 0;
	if (i > 0 && grid[i-1][j] == ON) neighbours++;
	if (i > 0 && j > 0 && grid[i-1][j-1] == ON) neighbours++;
	if (i > 0 && j < n - 1 && grid[i-1][j+1] == ON) neighbours++;
	if (j < n - 1 && grid[i][j+1] == ON) neighbours++;
	if (i < n - 1 && j < n - 1 && grid[i+1][j+1] == ON) neighbours++;
	if (i < n - 1 && grid[i+1][j] == ON) neighbours++;
	if (i < n - 1  && j > 0 && grid[i+1][j-1] == ON) neighbours++;
	if (j > 0 && grid[i][j-1] == ON) neighbours++;
	return neighbours;
}

void next_step (char** grid, int n) {
	int neighbours;
	char** grid2 = malloc(101 * 101 * sizeof(char));
	for (int i = 0; i < n; i++){
		grid2[i] = malloc(101 * sizeof(char));
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			neighbours = n_neighbours(grid, i, j, n);
	
			if (grid[i][j] == ON) {
				if (neighbours == 2 || neighbours == 3) {
					grid2[i][j] = ON;
				}
				else grid2[i][j] = OFF;
			}
			else {
				if (neighbours == 3) {
					grid2[i][j] = ON;
				}
				else grid2[i][j] = OFF;
			}
		}
	}

	for (int i = 0; i < n; i++) {
	       for (int j = 0; j < n; j++) {
	       		grid[i][j] = grid2[i][j];
	 	}
	}	
}

int main() {
	char** grid = malloc(101 * 101 * sizeof(char));
	int n = 100;
	for (int i = 0; i < n; i++){
		grid[i] = malloc(101 * sizeof(char));
		for (int j = 0; j < n; j++){
			grid[i][j] = getchar();
		}
		getchar();
	}
	

	for (int i = 0; i < n; i++){
		next_step(grid, n);
	}

	int counter = 0;

	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			counter += grid[i][j] == ON;
		}
	}

	printf("%d\n", counter);
    	return 0;
}
