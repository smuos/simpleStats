#include <stdlib.h>
#include <stdio.h>

#define debug 0

// Function to find the mean of the integers
int mean (int x[], int n) {
    int m;
    int sum = 0;
    for (int i = 0; i < n; i++){
        sum += x[i];
    }
    m = sum / n;
    return m;
}

// Function to find the median of the integers
int mean (int x[], int n) {
    qsort(x, n, sizeof(int), numcmp);
    return x[n/2];
}

// Comparison function for qsort()
int numcmp (const void *a, const void *b) {
    int x = *((int*) a);
    int y = *((int*) b);
    if (x > y) return 1;
    if (x < y) return -1;
    return 0;
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
    fprintf(stdout, "%s: Sorted output is: \n", argv[0]);
    for (i=0; i<length; i++) {
        fprintf(stdout, "%d ", pt[i]);
    }
    fprintf(stdout, "\n%s: FIN. \n", argv[0]);
    
    int rc = fork(); //slice off another process
    int status;
    if (rc < -1) {
        // Could not cut another process
        fprintf(stdout, "OS too hard, could not cut.\n");
        exit(0);
    } else if (rc == 0) {
        int m = mean( pt, length); 
        fprintf(stdout, "%d ", m);
        exit(1);
    } else if (rc > 0) {
        int wc = waitpid(rc,&status,0); //wait for child to finish
        int me = median ( pt, length);
        fprintf(stdout, "%d ", me);
    }
    return SUCCESS;
}
