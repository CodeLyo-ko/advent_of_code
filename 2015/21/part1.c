#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#define min(a,b) (a < b)?(a):(b)

typedef struct {
	int hp;
	int damage;
	int armor;
} stats_t;

typedef struct {
	int cost;
	int damage;
	int armor;
} item_t;

void add_stats(stats_t* player, item_t item){
	player->damage += item.damage;
	player->armor += item.armor;
}

int calculate_win(stats_t boss, stats_t player){
	int turn = 1;
	while (boss.hp > 0 && player.hp > 0) {
		if (turn) {
			boss.hp -= player.damage - boss.armor;
			if (player.damage - boss.armor <= 0) {
				boss.hp -= 1;
			}
		}
		else {
			player.hp -= boss.damage - player.armor;
			if (boss.damage - player.armor <= 0) {
				player.hp -= 1;
			}
		}
		turn = !turn;
	}
	return (player.hp > 0);
}

int min_gold(stats_t boss, stats_t player, item_t* weapons, int n_weapons, item_t* armor, int n_armor, item_t* rings, int n_rings, int item, int n_item, int rings_bought) {
	int mini = INT_MAX;
	int temp;
       	if (item == 0) {
		if (n_item == n_weapons) {
			return mini;
		}
		temp = min_gold(boss, player, weapons, n_weapons, armor, n_armor, rings, n_rings, item, n_item + 1, 0);
		mini = min(temp, mini); 
		add_stats(&player, weapons[n_item]);
		temp = weapons[n_item].cost + min_gold(boss, player, weapons, n_weapons, armor, n_armor, rings, n_rings, item + 1, 0, 0);
		mini = min(temp, mini); 
	}
	else if (item == 1) {
		if (n_item == n_armor) {
			return min_gold(boss, player, weapons, n_weapons, armor, n_armor, rings, n_rings, item + 1, 0, 0);
		}
		temp = min_gold(boss, player, weapons, n_weapons, armor, n_armor, rings, n_rings, item, n_item + 1, 0);
		mini = min(temp, mini); 
		add_stats(&player, armor[n_item]);
		temp = armor[n_item].cost + min_gold(boss, player, weapons, n_weapons, armor, n_armor, rings, n_rings, item + 1, 0, 0);
		mini = min(temp, mini); 
	}
	else {
		if (rings_bought == 2 || n_item == n_rings) {
			if (calculate_win(boss, player)){
				return 0;
			}
			else {
				return 500000;
			}
		}
		temp = min_gold(boss, player, weapons, n_weapons, armor, n_armor, rings, n_rings, item, n_item + 1, rings_bought);
		mini = min(temp, mini); 
		add_stats(&player, rings[n_item]);
		temp = rings[n_item].cost + min_gold(boss, player, weapons, n_weapons, armor, n_armor, rings, n_rings, item + 1, 0, rings_bought + 1);
		mini = min(temp, mini); 
	}
	return mini;
}	
			       
int main() {
	stats_t boss;
	boss.hp = 100;
	boss.damage = 8;
	boss.armor = 2;

	stats_t player;
	player.hp = 100;
	player.damage = 0;
	player.armor = 0;

	item_t* weapons = malloc(5 * sizeof(item_t));
	int n_weapons = 5;
	weapons[0].cost = 8;
	weapons[0].damage = 4;
	weapons[0].armor = 0;
	weapons[1].cost = 10;
	weapons[1].damage = 5;
	weapons[1].armor = 0;
	weapons[2].cost = 25;
	weapons[2].damage = 6;
	weapons[2].armor = 0;
	weapons[3].cost = 40;
	weapons[3].damage = 7;
	weapons[3].armor = 0;
	weapons[4].cost = 74;
	weapons[4].damage = 8;
	weapons[4].armor = 0;
	
	item_t* armor = malloc(5 * sizeof(item_t));
	int n_armor = 5;
	armor[0].cost = 13;	
	armor[1].cost = 31;	
	armor[2].cost = 53;	
	armor[3].cost = 75;	
	armor[4].cost = 102;	
	armor[0].damage = 0;
	armor[1].damage = 0;
	armor[2].damage = 0;
	armor[3].damage = 0;
	armor[4].damage = 0;
	armor[0].armor = 1;
	armor[1].armor = 2;
	armor[2].armor = 3;
	armor[3].armor = 4;
	armor[4].armor = 5;

	item_t* rings = malloc(6 * sizeof(item_t));
	int n_rings = 6;
	rings[0].cost = 25;
	rings[1].cost = 50;
	rings[2].cost = 100;
	rings[3].cost = 20;
	rings[4].cost = 40;
	rings[5].cost = 80;
	rings[0].damage = 1;
	rings[1].damage = 2;
	rings[2].damage = 3;
	rings[3].damage = 0;
	rings[4].damage = 0;
	rings[5].damage = 0;
	rings[0].armor = 0;
	rings[1].armor = 0;
	rings[2].armor = 0;
	rings[3].armor = 1;
	rings[4].armor = 2;
	rings[5].armor = 3;

	printf("%d\n", min_gold(boss, player, weapons, n_weapons, armor, n_armor, rings, n_rings, 0, 0, 0));

	return 0;
}
