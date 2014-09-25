// mm.c

/*
A simple C program to calculate the mean and median
of input numbers.
*/

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

// Function to calculate the mean
double mean (int *num, int length) {
    double sum = 0;
    int i;
    for (i=0; i<length; i++)
        sum += num[i];
    return sum / length;
}

// Function to calculate the median
double median (int *num, int length)  {
    int midIndex = length / 2;
    if (length%2 == 0)
        return (num[midIndex-1] + num[midIndex]) / 2;
    else return num[midIndex];
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
    fprintf(stdout, "%s: Sorted output is: ", argv[0]);
    for (i=0; i<length; i++) {
        fprintf(stdout, "%d ", pt[i]);
    }

    // avoid printing out the numbers twice
    fflush(stdout);

    // Forking below
    int rc = fork();
    if (rc < 0)     //fork failed, exit
    {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc == 0)   //Child calls function and prints median
    {
        fprintf(stdout, "\n%s: Median is: %f", argv[0], median(pt,length));
    }
    else        //Parent calls and prints mean
    {
        // make parent wait until child is finished
        wait(NULL);
        fprintf(stdout, "\n%s: Mean is: %f  \n",argv[0], mean(pt,length));
        fprintf(stdout, "%s: FIN. \n", argv[0]);
    }

    return 0;
}
