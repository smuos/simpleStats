#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define debug 0

// Comparison function for qsort()
int numcmp (const void *a, const void *b) {
    int x = *((int*) a);
    int y = *((int*) b);
    if (x > y) return 1;
    if (x < y) return -1;
    return 0;
}

// Calculuate the Mean
float mean (int *numbers, int length) {
    float sum = 0;
    for (int i=0; i<length; i++)
    {
        sum += numbers[i];
    }
    return sum / length;
}

// Calculuate the Median, assumes array is sorted
float median (int *numbers, int length) {
    int middleIndex = length / 2;
    if (length % 2 == 0) 
        return (numbers[middleIndex - 1] + numbers[middleIndex]) / 2.0;
    else return numbers[middleIndex];
}

int main(int argc, char *argv[]) {

    int i, length, *pt;
    
    // Check for proper usage
    if (argc < 2) {
        fprintf(stderr, "%s: Aborting, not enough arguments.\n", argv[0]);
        return (-1);
    }

    // Determine amount of numbers from argc
    length = argc - 1;
#if debug
    fprintf(stderr, "%s: DEBUG: %d numbers were passed.\n", argv[0], length);
#endif

    // Allocate memory for array of number (and error check)
    if ((pt = malloc(length * sizeof(int))) == NULL) {
        fprintf(stderr, "%s: Could not allocate memory.\n", argv[0]);
    }
        
    // Read numbers into array
    for (i = 0; i < length; i++) {
        pt[i] = (int) strtol(argv[i+1], NULL, 10);
    }

    // Sort numbers
    qsort(pt, length, sizeof(int), numcmp);

    // Print out numbers
    fprintf(stdout, "%s:(%d) Sorted output is: \n", argv[0], getpid());
    for (i=0; i<length; i++) {
        fprintf(stdout, "%d ", pt[i]);
    }
    printf("\n"); // This is required otherwise it runs the for loop twice?

    // Fork the process
    int returnCode = fork();
    if (returnCode < 0) {
        fprintf(stderr, "%s: DEBUG: fork failed: returnCode: %d.\n", argv[0], returnCode);
    } else if (returnCode == 0) {
        // Child Print Median
        float calculatedMedian = median(pt, length);
        fprintf(stdout, "\n%s:(%d C) Median is: %.3f", argv[0], getpid(), calculatedMedian);
    } else if (returnCode > 0) {
        // Parent Print Mean
        float calculatedMean = mean(pt, length);
        fprintf(stdout, "\n%s:(%d P) Mean is: %.3f", argv[0], getpid(), calculatedMean);
    }

    fprintf(stdout, "\n%s: FIN. \n", argv[0]);

    return 0;
}