#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
	char* beg;
	char* end;
} replace_t;

void new_molecule(char* molecule, int i, int j, char* replace, char* new){
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
//	printf("new: %s %s %d %d %d\n", new, molecule, i, j, size_total);
}

int cmp_string(const void* str1, const void* str2) {
	const char* rec1 = *(char**)str1;
	const char* rec2 = *(char**) str2;

	return strlen(rec1) - strlen(rec2);
}

int n_steps(char* molecule_end, char* molecule_now, replace_t* replacements, int n){
	//printf("|%s| |%s|\n", molecule_end, molecule_now);
	if (!strcmp(molecule_now, molecule_end)){
		return 0;
	}
	
	int min_steps = INT_MAX - 1;

	char** temp = malloc(5000 * 500 * sizeof(char));
	int n_temp = 0;

	int n_molecule = strlen(molecule_now);
	for (int i = 0; i < n_molecule; i++){
		for (int j = 0; j < n; j++){
			int k = 0;
			while (replacements[j].beg[k] != '\0' && replacements[j].beg[k] == molecule_now[k + i]){
				k++;
			}
			if (replacements[j].beg[k] != '\0'){
				continue;
			}
			temp[n_temp] = malloc(5000 * sizeof(char));
			new_molecule(molecule_now, i, k, replacements[j].end, temp[n_temp]);
			n_temp++;
		}
	}
	qsort(temp, n_temp, sizeof(char*), cmp_string);

	for (int i = 0; i < n_temp; i++) {
		int steps = n_steps(molecule_end, temp[i], replacements, n) + 1;
		min_steps = (min_steps < steps) ? min_steps: steps;
		if (min_steps < INT_MAX - 1)
			return min_steps;
	}
	return min_steps;
}

int compare_replace_t( const void* a, const void* b) {
	return (strlen((*(replace_t*)b).beg) - strlen((*(replace_t*)a).beg));
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
		while((replacements[n].end[i] = getchar()) != ' '){
			i++;
		}
		replacements[n].end[i] = '\0';
		while (getchar() != ' ');
		i = 0;
		while((replacements[n].beg[i] = getchar()) != '\n'){
			i++;
		}
		replacements[n].beg[i] = '\0';
		n++;
	}
	fgets(molecule, 5000, stdin);
	molecule[strlen(molecule) - 1] = '\0';
	qsort(replacements, n, sizeof(replace_t), compare_replace_t);
	printf("%s\n", replacements[0].beg);
	printf("%d\n", n_steps("e", molecule, replacements, n ));
		
    	return 0;
}
