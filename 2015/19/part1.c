#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
	char* beg;
	char* end;
} replace_t;

void add_molecule(char** all_molecules, int* n, char* molecule, int i, int j, char* replace){
	char* new = malloc(5000 * sizeof(char));
	for (int k = 0; k < i; k++){
		new[k] = molecule[k];
	}
	int size_replace = strlen(replace);
	for (int k = i; k < i + size_replace; k++) {
		new[k] = replace[k - i];
	}
	int size_total = strlen(molecule) - j + size_replace;
	for (int k = i + size_replace; k < size_total; k++){
		new[k] = molecule[k - size_replace + j];
	}
	new[size_total] = '\0';

	for (int k = 0; k < *n; k++){
		if (!strcmp(all_molecules[k], new)){
			return;
		}	
	}
	all_molecules[*n] = strdup(new);
	(*n)++;
}
int main() {
	replace_t* replacements = malloc(200 * sizeof(replace_t));
	int n = 0;
	char* molecule = malloc(5000 * sizeof(char));
	while(getchar() != '\n'){
		fseek(stdin, -1, SEEK_CUR);
		replacements[n].beg = malloc(10 * sizeof(char));
		replacements[n].end = malloc(10 * sizeof(char));
		int i = 0;
		while((replacements[n].beg[i] = getchar()) != ' '){
			i++;
		}
		replacements[n].beg[i] = '\0';
		while (getchar() != ' ');
		i = 0;
		while((replacements[n].end[i] = getchar()) != '\n'){
			i++;
		}
		replacements[n].end[i] = '\0';
		n++;
	}
	fgets(molecule, 5000, stdin);
	printf("%d\n", strlen(molecule));
	char** all_molecules = malloc(5000 * 500 * sizeof(char));
	int n_distinct = 0;
	int n_molecule = strlen(molecule);
	for (int i = 0; i < n_molecule; i++){
		for (int j = 0; j < n; j++){
			int k = 0;
			while (replacements[j].beg[k] != '\0' && replacements[j].beg[k] == molecule[k + i]){
				k++;
			}
			if (replacements[j].beg[k] != '\0'){
				continue;
			}
			add_molecule(all_molecules, &n_distinct, molecule, i, k, replacements[j].end);
		}
	}
	printf("%d\n", n_distinct);
		
    	return 0;
}
