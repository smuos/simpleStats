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

/* mean and median functions */
int mean(int* pt,int length) {

    int i = 0;
    int sum = 0;
    int mean = 0;
    for(i = 0; i < length; i++){
        sum = sum + pt[i];
    }
    mean = (sum / length);

    return mean;
}

int median(int* pt,int length){
    int middle, median;

    middle = (length / 2);
    median = pt[middle];

    return median;

}

/* -------------------------- */

int main(int argc, char *argv[]) {

    int i, length, *pt;
    /* my vars */
    int meanVal, medianVal;
    
    // Check for proper usage
    if (argc < 2) {
        fprintf(stderr, "%s: Aborting, not enough arguments.\n", argv[0]);
        return (-1);
    }

    // Determine number of numbers from argc
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
    fprintf(stdout, "%s: Sorted output is: \n", argv[0]);
    for (i=0; i<length; i++) {
        fprintf(stdout, "%d ", pt[i]);
    }


    /* Forking!!! :O */

    int rc = fork();
    if (rc < 0) {       
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) { 
        medianVal = median(pt, length);
        fprintf(stdout, "Median: %d\n", medianVal);
    } else {
        meanVal = mean(pt, length);
        fprintf(stdout, "Mean: %d\n", meanVal);
    } 

    /* That's all, folks */
    fprintf(stdout, "\n%s: FIN. \n", argv[0]);

    
    return 0;
}

