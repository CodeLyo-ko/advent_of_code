#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INPUT 36000000
int main() {
	int* houses = malloc(INPUT * sizeof(int));
	for (int i = 0; i < INPUT; i++){
		houses[i] = 10;
	}
	for (int i = 2; i < INPUT; i++){
		for (int j = 0; j < INPUT && j <= i * 50; j+=i){
			houses[j] += i * 11;
		}
	}

	for (int i = 0; i < INPUT; i++){
		if (houses[i] >= INPUT){
			printf("%d\n", i);
			break;
		}
	}
	return 0;
}
