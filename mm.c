#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define debug 0

//Mean calculating function
double mean(int *pt, int length)
{
    int sum = 0;
    for(int i = 0; i < length; i++)
    {
        sum = sum + pt[i];
    }
    return ((double)sum/length);
}

//Median calculating function
double median(int *pt, int length)
{	
    if(length % 2 == 1)
    {
        return pt[(length/2)];
    }
    else
    {
	int* midVals;
        if((midVals = malloc(2 * sizeof(int))) == NULL) 
        {
            fprintf(stderr, "Could not allocate memory.\n");
        }
        midVals[0] = pt[((length/2) - 1)];
        midVals[1] = pt[(length/2)];
        return mean(midVals, 2);
    }
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
    fprintf(stdout, "The median is: %.2f \n", median(pt, length));
    return 0;
}
