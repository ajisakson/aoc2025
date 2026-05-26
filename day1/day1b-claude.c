#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    struct timespec t0, t1;
    clock_gettime(CLOCK_MONOTONIC, &t0);

    FILE *f = fopen("day1/input-a", "r");
    if (!f) {
        f = fopen("input-a", "r");
        if (!f) {
            perror("open input");
            return 1;
        }
    }

    int pos = 50;
    long zeros = 0;

    char dir;
    int dist;
    while (fscanf(f, " %c%d", &dir, &dist) == 2) {
        if (dir == 'R') {
            zeros += (pos + dist) / 100;
            pos = (pos + dist) % 100;
        } else {
            int first = (pos == 0) ? 100 : pos;
            if (dist >= first) zeros += 1 + (dist - first) / 100;
            pos = ((pos - dist) % 100 + 100) % 100;
        }
    }

    fclose(f);

    clock_gettime(CLOCK_MONOTONIC, &t1);
    double elapsed_us = (t1.tv_sec - t0.tv_sec) * 1e6
                      + (t1.tv_nsec - t0.tv_nsec) / 1e3;

    printf("Part 2: %ld\n", zeros);
    printf("Elapsed: %.3f us\n", elapsed_us);
    return 0;
}
