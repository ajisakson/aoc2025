#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void){

    FILE* f = fopen("input-a", "r");
    if (!f) return -1;

    fseek(f, 0, SEEK_END);
    int length = ftell(f);
    fseek(f, 0, SEEK_SET);

    char* rangesString = malloc(length + 1);
    if(rangesString){
        fread(rangesString, 1, length, f);
        rangesString[length] = '\0';
    }

    fclose(f);

    int rangeLen = 1, curLen = 0, maxLen = 0;
    for (int r = 0; rangesString[r] != '\0'; r++){
        if (rangesString[r] == ',') {
            rangeLen++;
            if (curLen > maxLen) maxLen = curLen;
            curLen = 0;
        } else {
            curLen++;
        }
    }

    char **ranges;

    ranges = malloc(rangeLen * sizeof(char*));
    for (int i = 0; i < rangeLen; i++){
        ranges[i] = malloc((maxLen+1) * sizeof(char));
    }
    // break up ranges into string by comma
    char *token = strtok(rangesString,",");
    int tokenCount = 0;
    while (token != NULL){
        ranges[tokenCount] = token;
        tokenCount++;
        token = strtok(NULL, ",");
    }

    long long *invalid[] = {};
    int invalidLen = 0;
    long long sum = 0;
    // for each range
    for (int i = 0; i < rangeLen; i++){
        // read into high and low numbers via string interp %i%c%i
        long long min = 0, max = 0;
        sscanf(ranges[i], "%lli-%lli", &min, &max);
        printf("range: %lli-%lli\n", min, max);
        // for each integer in range between low and high
        for (long long j = min; j <= max; j++){
            // convert j to string
            char intStr[maxLen] = {};
            sprintf(intStr, "%lli", j);

            // if number of digits % 2 == 0
            if (strlen(intStr) % 2 == 0){
            // if string chars [0] length of digits / 2 == string chars [1] lenght of digits / 2

                int compareSize = strlen(intStr) / 2;
                char string1[compareSize], string2[compareSize];
                strncpy(string1, intStr, compareSize);
                strncpy(string2, intStr + compareSize, compareSize);
                if(strncmp(string1, string2, compareSize) == 0){
                    //append string to array as int
                    long long val = atoll(intStr);
                    printf("value: %lli\n",val);
                    sum = val + sum;
                        

                    // printf("%i\n", val);
                    // *invalid = realloc(invalid, invalidLen + 1);
                    
                    // invalid[i] = &val;
                    // invalidLen++;
                }
            }
        }
    }
    // sum items in array and print out
    for (int k = 0; k < invalidLen; k++){
        sum = sum + *invalid[k];
    }

    printf("sum: %lli\n", sum);
    free(ranges);
    return 0;
}
