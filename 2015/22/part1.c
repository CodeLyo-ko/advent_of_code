#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define min(a,b) (a < b)?(a):(b)
#define MAX_INT LLONG_MAX

typedef struct {
	int hp;
	int damage;
	int armor;
	int mana;
} stats_t;

typedef struct {
	int timer;
	int timer_reset;
	int armor;
	int damage;
	int mana;
} effect_t;

typedef struct {
	int cost;
	int damage;
	int heal;
	int effect;
} spell_t;

void apply_effects(effect_t* active_effects, int n_effects, stats_t* boss, stats_t* player) {
    player->armor = 0;
    for (int i = 0; i < n_effects; i++) {
        if (active_effects[i].timer == 0) {
            continue;
        }
        active_effects[i].timer--;
        player->armor += active_effects[i].armor;
        boss->hp -= active_effects[i].damage;
        player->mana += active_effects[i].mana;
    }
}

effect_t* copy_effects(effect_t* input, int n) {
    effect_t* output = malloc(n * sizeof(effect_t));
    for (int i = 0; i < n; i++){
        output[i] = input[i];
    }
    return output;
}

void cast_spell(spell_t spell, effect_t* active_effects, stats_t* boss, stats_t* player) {
    player->mana -= spell.cost;
    boss->hp -= spell.damage;
    player->hp += spell.heal;
    if (spell.effect != -1) {
        active_effects[spell.effect].timer = active_effects[spell.effect].timer_reset;
    }
}

void boss_attack(stats_t boss, stats_t* player) {
    int damage = boss.damage - player->armor;
    if (damage < 1) damage = 1;
    player->hp -= damage;
}

long long min_mana(effect_t* active_effects, int n_effects, spell_t* spells, int n_spells, stats_t boss, stats_t player) {
    long long minimum = MAX_INT;
    for (int i = 0; i < n_spells; i++) {
        effect_t* new_effects = copy_effects(active_effects, n_effects);
        stats_t new_boss = boss;
        stats_t new_player = player;

        apply_effects(new_effects, n_effects, &new_boss, &new_player);
        if (spells[i].cost > new_player.mana) {
            free(new_effects);
            continue;
        }
        if (spells[i].effect != -1 && new_effects[spells[i].effect].timer != 0) {
            free(new_effects);
            continue;
        }
        long long temp = spells[i].cost;
        cast_spell(spells[i], new_effects, &new_boss, &new_player);
        if (new_boss.hp <= 0) {
            free(new_effects);
            return temp;
        }
        
        apply_effects(new_effects, n_effects, &new_boss, &new_player);
        if (new_boss.hp <= 0) {
            free(new_effects);
            return  temp;
        }
        boss_attack(new_boss, &new_player);
        if (new_player.hp <= 0) {
            free(new_effects);
            continue;
        }

        long long next = min_mana(new_effects, n_effects, spells, n_spells, new_boss, new_player);
        if (next != MAX_INT) {
            minimum = min(minimum, temp + next);
        }
        free(new_effects);
    }
    return minimum;
}

int main() {
	stats_t boss;

	boss.hp = 71;
	boss.damage = 10;
	boss.armor = 0;
	boss.mana = 0;

	stats_t player;
	player.hp = 50;
	player.damage = 0;
	player.armor = 0;
	player.mana = 500;

	effect_t* effects = malloc(3 * sizeof(effect_t));
	int n_effect = 3;
	effects[0].timer = 0;
	effects[1].timer = 0;
	effects[2].timer = 0;
	effects[0].timer_reset = 6;
	effects[1].timer_reset = 6;
	effects[2].timer_reset = 5;
	effects[0].armor = 7;
	effects[1].armor = 0;
	effects[2].armor = 0;
	effects[0].damage = 0;
	effects[1].damage = 3;
	effects[2].damage = 0;
	effects[0].mana = 0;
	effects[1].mana = 0;
	effects[2].mana = 101;

	spell_t* spells = malloc(5 * sizeof(spell_t));
	int n_spell = 5;
	spells[0].cost = 53;
	spells[0].damage = 4;
	spells[0].heal = 0;
	spells[0].effect = -1;
	spells[1].cost = 73;
	spells[1].damage = 2;
	spells[1].heal = 2;
	spells[1].effect = -1;
	spells[2].cost = 113;
	spells[2].damage = 0;
	spells[2].heal = 0;
	spells[2].effect = 0;
	spells[3].cost = 173;
	spells[3].damage = 0;
	spells[3].heal = 0;
	spells[3].effect = 1;
	spells[4].cost = 229;
	spells[4].damage = 0;
	spells[4].heal = 0;
	spells[4].effect = 2;

  printf("%lld\n", min_mana(effects, n_effect, spells, n_spell, boss, player));

	return 0;
}
