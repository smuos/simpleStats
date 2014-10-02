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

float mean (int* values, int length) { //float function to calculate upto two decimal places
    float sum = 0;
    for (int i = 0; i < ength; i++) {
      sum +=values[i];
      }
    return sum / length;
}

float median (int* values, int length) {
    int middle = length / 2;
    if (length % 2 == 0) { //check if the total number is even/odd
        return(values[middle - 1] + values[middle]) / 2;
    } else {
        return values[middle];
    }
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
    fprintf(stdout, "%s:(%d) Sorted output is: \n", argv[0], (int)getpid());
    for (i=0; i<length; i++) {
        fprintf(stdout, "%d ", pt[i]);
    }
    
    int slice = fork(); //system call
    if (slice < 0) {
    fprintf(stderr, "%s: Failure: fork didnt run properly!);
    } else if (slice == 0) { //print the median
    fprintf(stdout, "\n%s:(%d C) Median =  %.2f", argv[0], 
        (int)getpid(), median(pt, length));
    } else if (slice > 0) {
    int pause = wait(NULL); //system call to make parent wait
    fprintf(stdout, "\n%s:(%d P, %d PS) Mean is: %.3f", argv[0],
        (int)getpid(), pause, mean(pt, length));
    }


    fprintf(stdout, "\n%s: FIN. \n", argv[0]);

    return 0;
}
