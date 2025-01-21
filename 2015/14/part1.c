#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
    int speed;
    int speed_time;
    int rest_time;
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

        n_reindeers++;
    }

    int seconds = 2503;

    int max_km = 0;

    int s_cur = 0;
    int s = 0;
    int km_cur = 0;
    int resting = 0;

    for (int i = 0; i < n_reindeers; i++) {
        s = 0;
        km_cur = 0;
        resting = 0;

        for (s_cur = 0; s_cur < seconds; s_cur++) {
            if (!resting) {
                km_cur += reindeers[i].speed;
                s++;
                if (s == reindeers[i].speed_time) {
                    resting = 1;
                    s = 0;
                }
            }

            else {
                s++;
                if (reindeers[i].rest_time == s) {
                    resting = 0;
                    s = 0;
                }
            }
        }

        if (km_cur > max_km) {
            max_km = km_cur;
        }
    }

    printf("%d\n", max_km);
    return 0;
}
