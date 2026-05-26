#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ITERS 100000

typedef struct { char dir; int dist; } Rot;

static long algo_austin(const Rot *rots, int n) {
    int pos = 50;
    long zeroCount = 0;
    for (int i = 0; i < n; i++) {
        char direction = rots[i].dir;
        int magnitude = rots[i].dist;
        int step = (direction == 'R') ? 1 : -1;
        int vector = step * magnitude;
        zeroCount += (magnitude / 100);
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
    return zeroCount;
}

static long algo_claude(const Rot *rots, int n) {
    int pos = 50;
    long zeros = 0;
    for (int i = 0; i < n; i++) {
        char dir = rots[i].dir;
        int dist = rots[i].dist;
        if (dir == 'R') {
            zeros += (pos + dist) / 100;
            pos = (pos + dist) % 100;
        } else {
            int first = (pos == 0) ? 100 : pos;
            if (dist >= first) zeros += 1 + (dist - first) / 100;
            pos = ((pos - dist) % 100 + 100) % 100;
        }
    }
    return zeros;
}

static double elapsed_us(struct timespec a, struct timespec b) {
    return (b.tv_sec - a.tv_sec) * 1e6 + (b.tv_nsec - a.tv_nsec) / 1e3;
}

int main(void) {
    FILE *f = fopen("input-a", "r");
    if (!f) { perror("open"); return 1; }

    Rot *rots = malloc(sizeof(Rot) * 8192);
    int n = 0;
    char dir; int dist;
    while (fscanf(f, " %c%d", &dir, &dist) == 2) {
        rots[n].dir = dir;
        rots[n].dist = dist;
        n++;
    }
    fclose(f);
    printf("Parsed %d rotations, running each algo %d times\n\n", n, ITERS);

    struct timespec t0, t1;
    volatile long sink = 0;

    // warm up caches
    for (int i = 0; i < 100; i++) { sink ^= algo_austin(rots, n); sink ^= algo_claude(rots, n); }

    // austin
    clock_gettime(CLOCK_MONOTONIC, &t0);
    long ra = 0;
    for (int i = 0; i < ITERS; i++) ra = algo_austin(rots, n);
    clock_gettime(CLOCK_MONOTONIC, &t1);
    double ta = elapsed_us(t0, t1);
    sink ^= ra;

    // claude
    clock_gettime(CLOCK_MONOTONIC, &t0);
    long rc = 0;
    for (int i = 0; i < ITERS; i++) rc = algo_claude(rots, n);
    clock_gettime(CLOCK_MONOTONIC, &t1);
    double tc = elapsed_us(t0, t1);
    sink ^= rc;

    printf("austin: result=%ld  total=%.2f ms  per-iter=%.3f us\n", ra, ta/1000.0, ta/ITERS);
    printf("claude: result=%ld  total=%.2f ms  per-iter=%.3f us\n", rc, tc/1000.0, tc/ITERS);
    printf("ratio:  claude is %.2fx %s\n",
        ta > tc ? ta/tc : tc/ta, ta > tc ? "faster" : "slower");

    free(rots);
    (void)sink;
    return 0;
}
