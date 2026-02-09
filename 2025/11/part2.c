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

long int n_path(long int* cache, device_t* devices, int n_device, int start, int end) {
    if (cache[start] != -1) {
        return cache[start];
    }
    device_t cur = devices[start];

    long int res = 0;
    for (int i = 0; i < cur.n; i++) {
        if (cur.output[i] == end) {
            res++;
        }
        else {
            if (cur.output[i] == -1) continue;
            res += n_path(cache, devices, n_device, cur.output[i], end);
        }
    }
    cache[start] = res;
    return res;
}

void reset_cache(long int* cache, int n){
    for (int i = 0; i < n; i++) {
        cache[i] = -1;
    }
}

int main() {
    device_t* devices = malloc(MAX_ * sizeof(int));
    int n_device = 0;
    char id[3];

    while (getchar() != EOF) {
        fseek(stdin, -1, SEEK_CUR);
        scanf("%3s:", id);
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

    int svr = get_id(devices, n_device, "svr");
    int dac = get_id(devices, n_device, "dac");
    int fft = get_id(devices, n_device, "fft");
    int out = -1;

    long int* cache = malloc(n_device * sizeof(long int));
    reset_cache(cache, n_device);
    long int svr_fft = n_path(cache, devices, n_device, svr, fft);
    reset_cache(cache, n_device);
    long int fft_dac = n_path(cache, devices, n_device, fft, dac);
    reset_cache(cache, n_device);
    long int dac_out = n_path(cache, devices, n_device, dac, out);
    reset_cache(cache, n_device);
    long int svr_dac = n_path(cache, devices, n_device, svr, dac);
    reset_cache(cache, n_device);
    long int dac_fft = n_path(cache, devices, n_device, dac, fft);
    reset_cache(cache, n_device);
    long int fft_out = n_path(cache, devices, n_device, fft, out);

    long int res = svr_fft * fft_dac * dac_out + svr_dac * dac_fft * fft_out;
    printf("%ld\n", res);


    return 0;
}
