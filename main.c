#include <stdio.h>
#include <stdlib.h>

static const int NUM_NUMS = 10000;
static const char INPUT_FILE[] = "./tests/coursera_sample.txt";
int debug = 0;
long numCompare = 0;

int quicksort(int* arr, int n);
int partition(int* arr, int n);

int main() {
    char line[80];
    int *arr = malloc(sizeof(int) * NUM_NUMS);
    long i = 0;
    FILE  *fr;

    fr = fopen(INPUT_FILE, "rt");

    // get a line, up to 80 chars from fr.  done if NULL
    printf("Reading file...\n");
    while(fgets(line, 80, fr) != NULL) {
        sscanf (line, "%d", arr+i);

        if(debug) {
            printf("%d\n", *(arr+i));
        }

        i++;

        if (i > NUM_NUMS) {
            printf("Too many numbers, could not read all\n");
            exit(-1);
        }
    }

    printf("Done reading file.\n");

    quicksort(arr, NUM_NUMS);

    if(debug) {
        printf("arr: [");
        for(i=0; i<NUM_NUMS; i++) {
            printf("%d ", *(arr+i));
        }
        printf("]\n");
    }

    fclose(fr);
    return 0;
}

int quicksort(int* arr, int n) {
    if(n <= 1) {
        return 0;
    }

    int pivotIndex = partition(arr, n);

    quicksort(arr, pivotIndex);
    quicksort(arr + pivotIndex, n - pivotIndex - 1);

    return 0;
}

/**
* Returns the final index of the first element in the
* array.
*/
int partition(int* arr, int n) {
    // Take the first element as the pivot
    int pivot = *arr;
    int i = 1;
    int j;
    int temp;

    for(j=1; j<n; j++) {
        if(*(arr+j) < pivot) {
            temp = *(arr+j);
            *(arr+j) = *(arr+i);
            *(arr+i) = temp;
            i++;
        }
    }

    temp = *(arr);
    *(arr) = *(arr+i-1);
    *(arr+i-1) = temp;

    return i-1;
}
