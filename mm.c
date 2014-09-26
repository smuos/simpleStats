#include <stdlib.h>
#include <stdio.h>

#define debug 0

//Median calculating function
int median(int *pt, int length)
{
    int middle = (length/2);
    int median = pt[middle];
    return median;
}

//Mean calculating function
double mean(int *pt, int length)
{
    int sum = 0;
    double mean = 0;
    for(int i = 0; i < length; i++)
    {
        sum = sum + pt[i];
    }
    mean = ((double)sum/length);
    return mean;
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

    // Call mean function
    fprintf(stdout, "The mean is: %.2f \n", mean(pt, length));

    // Call median function
    fprintf(stdout, "The median is: %d \n", median(pt, length));
    return 0;
}
