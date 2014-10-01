#include <stdlib.h>
#include <stdio.h>


#define debug 0

// Comparison function for qt[]);
int numcmp (const void *a, const void *b) {
    int x = *((int*) a);
    int y = *((int*) b);
    if (x > y) return 1;
    if (x < y) return -1;
    return 0;
}

// mean() function to calculate
double mean (int length, int *pt)
{
    int i, sum;
    double mean;
    sum = 0;
    for (i=0; i<length; i++)
    {
        sum += pt[i];
    }   
    mean = sum /(double)length;
    return mean;
}

// median() function to calculate median
double median (int length, int *pt)
{
    double median; 
    if (length%2 == 0)
    {
        median = (pt[length/2 - 1] + pt[length/2])/2;
    }
    else
    {
        median = pt[length/2];
    }
    return median;
}


int main(int argc, char *argv[]) {
     
    int i, length, *pt;
     
    // Check for proper usage
    if (argc < 2) {
        fprintf(stderr, "%s: Aborting, not enough arguments.\n", argv[0]);
        //return (-1);
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
     
    //Mean
    fprintf(stdout, "Mean: %d", mean(length, pt));

	//Median
    fprintf(stdout, "Median: %d", median(length, pt));  
     
    // Print out numbers
    fprintf(stdout, "%s: Sorted output is: \n", argv[0]);
    for (i=0; i<length; i++) {
        fprintf(stdout, "%d ", pt[i]);
    }
    fprintf(stdout, "\n%s: FIN. \n", argv[0]);

    return 0;
}
