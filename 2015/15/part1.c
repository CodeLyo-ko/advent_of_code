#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) (a) < (b) ? (b) : (a)

typedef struct {
    int capacity;
    int durability;
    int flavor;
    int texture;
    int calories;
    int quantity;
} ingredient_t;

long long calculate_score(ingredient_t* ingredients, int n) {
    long long capacity = 0;
    long long durability = 0;
    long long flavor = 0;
    long long texture = 0;

    for (int i = 0; i < n; i++) {
        capacity += ingredients[i].capacity * ingredients[i].quantity;
        durability += ingredients[i].durability * ingredients[i].quantity;
        flavor += ingredients[i].flavor * ingredients[i].quantity;
        texture += ingredients[i].texture * ingredients[i].quantity;
    }

    if (capacity < 0 || durability < 0 || flavor < 0 || texture < 0) return 0;
    return capacity * durability * flavor * texture;
}

long long max_score(ingredient_t* ingredients, int n, int teaspoons_left, int cur_ingredient) {
    if (teaspoons_left == 0) {
        ingredients[cur_ingredient].quantity = 0;
        return calculate_score(ingredients, n);
    }

    if (cur_ingredient == n - 1) {
        ingredients[cur_ingredient].quantity = teaspoons_left;
        return calculate_score(ingredients, n);
    }

    long long temp;
    long long max = 0;
    for (int i = 0; i <= teaspoons_left; i++) {
        ingredients[cur_ingredient].quantity = i;
        temp =  max_score(ingredients, n, teaspoons_left - i, cur_ingredient + 1);
        max = MAX(max, temp);
    }

    return max;
}

int main() {
    ingredient_t* ingredients = malloc(10 * sizeof(ingredient_t));
    int n_ingredients = 0;

    char* buf = malloc(50 * sizeof(char));

    while(getchar() != EOF) {
        fseek(stdin, -1, SEEK_CUR);

        scanf("%s capacity %d, durability %d, flavor %d, texture %d, calories %d\n", buf, &ingredients[n_ingredients].capacity, &ingredients[n_ingredients].durability, &ingredients[n_ingredients].flavor, &ingredients[n_ingredients].texture, &ingredients[n_ingredients].calories);


        n_ingredients++;
    }
    free(buf);

    int teaspoons_left = 100;


    long long score = max_score(ingredients, n_ingredients, teaspoons_left, 0);
    printf("%lld\n", score);
}
