#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int main(void){
    // have to rethink this whole thing but taking some cues from the claude 1a because I can't unsee it.
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

    printf("Zero count: %i\n", zeroCount);
    return 0;
}
