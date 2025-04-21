#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define MAX_LONG 999999999999

int find_target_weight(int* packages, int n_packages) {
    int sum = 0;
    for (int i = 0; i < n_packages; i++) {
        sum += packages[i];
    }
    return sum/3;
}

void revert_array(int* array, int n) {
    for (int i = 0; i < n/2; i++) {
        int b = array[n - i - 1];
        array[n - i - 1] = array[i];
        array[i] = b;
    }
}

long find_group(int* packages, int n_packages, int n_total, int target_weight, int n_cur, int weight_cur, long qe_cur, int i) {
    if (n_cur == n_total) {
        if (target_weight != weight_cur) {
            return MAX_LONG;
        }
        else {
            return qe_cur;
        }
    }
    
    if (i >= n_packages) {
        return MAX_LONG;
    }
    
    long min_qe = find_group(packages, n_packages, n_total, target_weight, n_cur, weight_cur, qe_cur, i+1);
    
    int weight = packages[i];
    if (weight_cur + weight > target_weight) {
        return min_qe;
    }

    long temp = find_group(packages, n_packages, n_total, target_weight, n_cur + 1, weight_cur + weight, qe_cur * weight, i + 1);

    return temp < min_qe ? temp : min_qe;
}

int main() {
    int* packages = malloc(50 * sizeof(int));
    int n_packages = 0;

    while(scanf("%d", &packages[n_packages]) != EOF){
        n_packages++;
    }

    int target_weight = find_target_weight(packages, n_packages);
        
    revert_array(packages, n_packages);

    long min_qe = 0;
    
    for (int i = 1; i < n_packages; i++) {
        min_qe = find_group(packages, n_packages, i, target_weight, 0, 0, 1, 0);
        if (min_qe != MAX_LONG) {
            printf("%ld\n", min_qe);
            break;
        }
    }

    return 0;
}
