#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int main(){

    struct timespec t0, t1;
    clock_gettime(CLOCK_MONOTONIC, &t0);

    FILE *fptr;
    int position = 50;
    int zeroCount = 0;

    char rotation[6];

    fptr = fopen("input-a", "r");
    
    // for loop through each line, breaking off first char as the direction, if R go pos to 99 then modulo if greater than, else go neg then absolute? does modulo work on negative numbers? if resulting pos = 0, then increment zeroCount; 
    while (fgets(rotation, 6, fptr)){
        char direction = rotation[0];
        char vectorChar[5];

        strncpy(vectorChar, rotation + 1, 5);
        int vectorInt = atoi(vectorChar);

        if (direction == 'R'){
            position = position - vectorInt;
        } else {
            position = position + vectorInt;
        }

        position = position % 100;
        if (position < 0){
            position = position + 100;
        }
        if (position == 0){
            zeroCount = zeroCount + 1;
        }

       // printf("Rotation: %s. Direction: %c. Vector: %i. End position: %i\n",rotation, direction, vectorInt, position);
    }

    fclose(fptr);

    clock_gettime(CLOCK_MONOTONIC, &t1);
    double elapsed_us = (t1.tv_sec - t0.tv_sec) * 1e6
                      + (t1.tv_nsec - t0.tv_nsec) / 1e3;

    printf("%i\n", zeroCount);
    printf("Elapsed: %.3f us\n", elapsed_us);
    return zeroCount;
}
