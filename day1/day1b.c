#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int main(void){
    // have to rethink this whole thing but taking some cues from the claude 1a because I can't unsee it.
    struct timespec t0, t1;
    clock_gettime(CLOCK_MONOTONIC, &t0);

    FILE *f;
    f = fopen("input-a", "r");

    int pos = 50, zeroCount = 0, magnitude;
    char direction;

    while (fscanf(f, " %c%i", &direction, &magnitude) == 2){
        int step = (direction == 'R') ? 1 : -1;
        int vector = step * magnitude;
        zeroCount = zeroCount + (magnitude / 100);
        int startedAtZero = (pos == 0);
        pos = pos + (vector % 100);
        if (pos < 0) {
            if (!startedAtZero) zeroCount++;
            pos += 100;
        } else if (pos == 0) {
            if (!startedAtZero) zeroCount++;
        } else if (pos >= 100) {
            zeroCount++;
            pos -= 100;
        }
    }

    fclose(f);

    clock_gettime(CLOCK_MONOTONIC, &t1);
    double elapsed_us = (t1.tv_sec - t0.tv_sec) * 1e6
                      + (t1.tv_nsec - t0.tv_nsec) / 1e3;

    printf("Zero count: %i\n", zeroCount);
    printf("Elapsed: %.3f us\n", elapsed_us);
    return 0;
}
