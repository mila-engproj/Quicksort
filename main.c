#include <stdio.h>
#include <stdlib.h>

const int NUM_NUMS = 100000;
int debug = 0;

int main() {
    printf("Hello Quicksort!\n");

    char line[80];
    long *arr = malloc(sizeof(long) * NUM_NUMS);
    long i = 0;
    FILE  *fr;

    fr = fopen ("./tests/coursera_sample.txt", "rt");

    // get a line, up to 80 chars from fr.  done if NULL
    while(fgets(line, 80, fr) != NULL) {
        sscanf (line, "%ld", arr+i);
        printf("%ld\n", *(arr+i));
        i++;
        if (i > NUM_NUMS) {
            printf("Too many numbers, could not read all\n");
            exit(-1);
        }
    }

    fclose(fr);
    return 0;
}
