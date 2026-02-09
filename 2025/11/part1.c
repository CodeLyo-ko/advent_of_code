#include <stdio.h>
#include <stdlib.h>
#define MAX_ 20000

typedef struct {
    char id[3];
    int* output;
    int n;
} device_t;

int get_id(device_t* devices, int n, char id[3]) {
    if (id[0] == 'o' && id[1] == 'u' && id[2] == 't') return -1;

    for (int i = 0; i < n; i++) {
        if (devices[i].id[0] == id[0] && devices[i].id[1] == id[1] && devices[i].id[2] == id[2]) {
            return i;
        }
    }
}

int n_path(device_t* devices, int n_device, int start, int end) {
    device_t cur = devices[start];

    int res = 0;
    for (int i = 0; i < cur.n; i++) {
        if (cur.output[i] == end) { res++; }
        else {
            res += n_path(devices, n_device, cur.output[i], end);
        }
    }
    return res;
}

int main() {
    device_t* devices = malloc(MAX_ * sizeof(int));
    int n_device = 0;
    char id[3];
    int you;

    while (getchar() != EOF) {
        fseek(stdin, -1, SEEK_CUR);
        scanf("%3s:", id);
        if (id[0] == 'y' && id[1] == 'o' && id[2] == 'u') you = n_device;
        devices[n_device].id[0] = id[0];
        devices[n_device].id[1] = id[1];
        devices[n_device].id[2] = id[2];
        devices[n_device].n = 0;
        devices[n_device].output = malloc(MAX_ * sizeof(int));
        while (getchar() != '\n') {
        }
        n_device++;
    }

    int n_id;
    fseek(stdin, 0, SEEK_SET);
    for (int i = 0; i < n_device; i++) {
        scanf("%3s:", id);
        while (getchar() != '\n'){
            scanf("%3s", id);
            n_id = get_id(devices, n_device, id);
            devices[i].output[devices[i].n++] = n_id;
        }
    }

    int res = n_path(devices, n_device, you, -1);
    printf("%d\n", res);

    return 0;
}
