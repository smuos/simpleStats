#include <stdlib.h>
#include <stdio.h>

#define debug 0

// Comparison function for qsort()
int numcmp (const void *a, const void *b) {
    int x = *((int*) a);
    int y = *((int*) b);
    if (x > y) return 1;
    if (x < y) return -1;
    return 0;
}

//function to calculate the mean
double  mean (int *p, int length)
{
    int i;
    double total = 0;
    for (i = 0; i < length; i++)
    {
        total = total + p[i];
    }
    return total/length;
}

//function to find median  
double  median (int *p, int length)
{
    int i,  position;
    double medianValue;
    if (length%2 == 0)
    {
        position = length/2;
	medianValue = (double) (p[position-1] + p[position])/2;
    }
    else
    {
	position = length/2;
	medianValue = p[position];
    }
    return medianValue;
}
	
int main(int argc, char *argv[]) {

    int i, length, *pt;
    double medianValue, meanValue;    
    
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
	exit(1);
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
    
    //caling fork() and checking if call failed
    int rc = fork(); 
    if (rc < 0)
    {
        fprintf(stderr, "fork failed\n");
    }

    if (rc == 0) //if child
    {
         medianValue = median(pt, length);
         fprintf(stdout, "\nThe median is: %.2f\n", medianValue);
    }

    if (rc > 0)  //if parent
    {
	int wc = wait(NULL);
        meanValue = mean(pt, length);
        fprintf(stdout, "\nThe mean is: %.2f\n", meanValue);
    }

    fprintf(stdout, "\n%s: FIN. \n", argv[0]);
    return 0;
}
