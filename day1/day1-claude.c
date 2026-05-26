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
    long part1 = 0;

    char dir;
    int dist;
    while (fscanf(f, " %c%d", &dir, &dist) == 2) {
        int step = (dir == 'R') ? 1 : -1;
        pos = ((pos + step * dist) % 100 + 100) % 100;
        if (pos == 0) part1++;
    }

    fclose(f);

    clock_gettime(CLOCK_MONOTONIC, &t1);
    double elapsed_us = (t1.tv_sec - t0.tv_sec) * 1e6
                      + (t1.tv_nsec - t0.tv_nsec) / 1e3;

    printf("Part 1: %ld\n", part1);
    printf("Elapsed: %.3f us\n", elapsed_us);
    return 0;
}
