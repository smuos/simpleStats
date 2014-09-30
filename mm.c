#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#define debug 0

// Comparison function for qsort()
int numcmp (const void *a, const void *b) {
    int x = *((int*) a);
    int y = *((int*) b);
    if (x > y) return 1;
    if (x < y) return -1;
    return 0;
}

// Mean() function to calculate the mean
double mean(int *num, int length) {
    // Initialize sum
    double sum = 0;
    // Using a for loop to add all the numbers to sum
    for (int i=0; i<length; i++)
        sum += num[i];
    // Return the mean
    return sum/length;
}

// Median() function to calculate the median
double median(int *num, int length) {
    // If the array length is even
    if (length%2 == 0)
        // Return the average of the two median numbers
        return (num[length/2-1] + num[length/2]) / 2.0;
    // If the array length is odd
    else
        // Return the median
        return num[length/2];
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
    
    // Make fork(), have the parent call mean() and child call median()
    int rc = fork();
    
    if (rc < 0) {
        fprintf(stderr, "Fork Failed!\n");
        exit(0);
    } else if (rc == 0) {
        // Child call median()
        double child = median(pt, length);
        // Child process should print the results of median()
        fprintf(stdout, "This is child processing (pid:%d)\n", (int)getpid());
        fprintf(stdout, "The median value is %f\n", child);
    } else if (rc > 0) {
        // Parent call mean()
        double parent = mean(pt, length);
        // Wait for child process
        int wc = wait(NULL);
        printf("Waiting for child process (wc:%d)\n", wc);
        // Parent process should print the results of mean()
        fprintf(stdout, "This is parent processing (pid:%d)\n", (int)getpid());
        fprintf(stdout, "The mean value is %f\n", parent);
    }
    
    return 0;
}
