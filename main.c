#include <stdio.h>
#include <stdlib.h>

// Globals:
static const int NUM_NUMS = 100000;
static const char INPUT_FILE[] = "./tests/coursera_sample.txt";
int debug = 0;
long numCompare = 0;

// Function Defs:
int quicksort(int *arr, int n);
int partitionUsingFirst(int *arr, int n);
int partitionUsingLast(int *arr, int n);
int partitionUsingMedian(int *arr, int n);
void swap(int *a, int *b);
int medianIndex(int *a, int n);

// Main:
int main() {
    char line[80];
    int *arr = malloc(sizeof(int) * NUM_NUMS);
    long n = 0;
    int i;
    FILE  *fr;
    fr = fopen(INPUT_FILE, "rt");

    if(debug) {
        printf("Reading file...\n");
    }

    // Get a line from file, up to 80 chars. Done if NULL
    while(fgets(line, 80, fr) != NULL) {
        sscanf (line, "%d", arr+n);

        if(debug) {
            printf("%d\n", *(arr+n));
        }

        n++;

        if (n > NUM_NUMS) {
            printf("Too many numbers, could not read all\n");
            exit(-1);
        }
    }

    printf("Read %ld numbers.\n\n", n);

    if(debug) {
        printf("comparing %ld more nums\n", n-1);
    }
    numCompare += n - 1;

    // Sort input:
    quicksort(arr, n);

    int wholeOrPart = n < 25 ? n : 25;

    if(wholeOrPart != n) {
        printf("First and last %d numbers after quicksort: \n\n", wholeOrPart);
    }

    printf("[ ");
    for(i=0; i<wholeOrPart; i++) {
        printf("%d ", *(arr+i));
    }

    if(wholeOrPart != n) {
        printf("...\n  ");
        for(i=wholeOrPart; i>0; i--) {
            printf("%d ", *(arr+n-i));
        }
    }
    printf("]\n");

    printf("\nNumber Comparisons: %ld\n\n", numCompare);

    fclose(fr);
    return 0;
}

int quicksort(int *arr, int n) {
    if(n <= 1) {
        if(debug) {
            printf("return at %d numbers\n\n", n);
        }
        return 0;
    }

    // Partition array:
    int pivotIndex = partitionUsingMedian(arr, n);

    if(debug) {
        int i;
        printf("partitioned %d numbers around position %d:\n", n, pivotIndex+1);
        for(i=0; i<n; i++) {
            printf("%d ", *(arr+i));
        }
        printf("\n\n");
    }

    if(pivotIndex - 1 >= 0) {
        if(debug) {
            printf("comparing %d more nums\n", pivotIndex - 1);
        }
        numCompare += pivotIndex - 1 ;
        quicksort(arr, pivotIndex);
    }

    if(n - pivotIndex - 2 >= 0) {
        if(debug) {
            printf("comparing %d more nums\n", n - pivotIndex - 2);
        }
        numCompare += n - pivotIndex - 2;
        quicksort(arr + pivotIndex + 1, n - pivotIndex - 1);
    }

    return 0;
}

/**
* Returns the final index of the first element in the
* array.
*/
int partitionUsingFirst(int *arr, int n) {
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

/**
 * Partitions an array around its last element.
 *
 * @param arr Array to partition
 * @param n   Size of array
 * @return    The final index of the previously last element
 */
int partitionUsingLast(int *arr, int n) {
    swap(arr, arr+n-1);

    return partitionUsingFirst(arr, n);
}

int partitionUsingMedian(int *arr, int n) {
    int m = medianIndex(arr, n);
    if(debug) {
        printf("median is: %d\n", *(arr+m));
    }
    swap(arr, arr+m);

    return partitionUsingFirst(arr, n);
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;

    return;
}

int medianIndex(int *a, int n) {
    // Middle index
    int m = n/2 + n%2 - 1;

    if(*a < *(a+m)) {
        if(*a >= *(a+n-1)) {
            return 0;
        }

        else if(*(a+m) < *(a+n-1)) {
            return m;
        }
    }

    else {
        if(*a < *(a+n-1)) {
            return 0;
        }

        else if(*(a+m) >= *(a+n-1)) {
            return m;
        }
    }

    return n-1;
}
