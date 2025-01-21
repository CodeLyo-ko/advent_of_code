#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
    int speed;
    int speed_time;
    int rest_time;
    int time_cur;
    int km_cur;
    int points;
    int resting;
} reindeer_t;

int main() {
    reindeer_t* reindeers = malloc(20 * sizeof(reindeer_t));
    int n_reindeers = 0;

    char* name_temp = malloc(20 * sizeof(char));

    char* line = malloc(100 * sizeof(char));

    while (getchar() != EOF) {
        fseek(stdin, -1, SEEK_CUR);

        fgets(line, 100, stdin);

        sscanf(line, "%s can fly %d km/s for %d seconds, but then must rest for %d seconds.\n", name_temp, &(reindeers[n_reindeers].speed), &(reindeers[n_reindeers].speed_time), &(reindeers[n_reindeers].rest_time));

        reindeers[n_reindeers].name = malloc(20 * sizeof(char));
        strcpy(reindeers[n_reindeers].name, name_temp);
        reindeers[n_reindeers].time_cur = 0;
        reindeers[n_reindeers].km_cur = 0;
        reindeers[n_reindeers].points = 0;
        reindeers[n_reindeers].resting = 0;

        n_reindeers++;
    }

    int seconds = 2503;

    int max_km;

    for (int s = 0; s < seconds; s++) {
        max_km = 0;
        for (int i = 0; i < n_reindeers; i++) {
            reindeers[i].time_cur++;
            if (!reindeers[i].resting) {
                reindeers[i].km_cur += reindeers[i].speed;
                if (reindeers[i].time_cur == reindeers[i].speed_time) {
                    reindeers[i].time_cur = 0;
                    reindeers[i].resting = 1;
                }
            }
            else {
                if (reindeers[i].time_cur == reindeers[i].rest_time) {
                    reindeers[i].time_cur = 0;
                    reindeers[i].resting = 0;
                }
            }
            if (reindeers[i].km_cur > max_km) {
                max_km = reindeers[i].km_cur;
            }
        }

        for (int i = 0; i < n_reindeers; i++) {
            if (reindeers[i].km_cur == max_km) {
                reindeers[i].points++;
            }
        }
    }

    int max_points = 0;

    for (int i = 0; i < n_reindeers; i++) {
        if (reindeers[i].points > max_points) {
            max_points = reindeers[i].points;
        }
    }


    printf("%d\n", max_points);
    return 0;
}
