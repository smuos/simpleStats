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
int median (int length, int *pt)
{
	int median = 0;
	if(length % 2 == 0)
	{
		median = (pt[length/2] + pt[length/2-1])/2;
	}
	else 
		median = pt[(length-1)/2];
	return median;
}
int mean (int length, int *pt)
{
	int i;
	int sum = 0;
	for ( i = 0; i < length; i++)
	{
		sum = sum + pt[i];
	}
	return(sum/length);
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
    qsort(pt, length, sizeof(int), numcmp);

    // Print out numbers
    fprintf(stdout, "%s: Sorted output is: \n", argv[0]);
    for (i=0; i<length; i++) {
        fprintf(stdout, "%d ", pt[i]);
    }
    printf("\n");
    int rc = fork();	//calling the fork method
    if(rc < 0) // fork failed
    {
	fprintf(stderr, "fork failed!\n");
	exit(1);
    }
    else if(rc == 0)	//child call median()
    {
	int medianValue = median(length, pt);
	//Child printing the results of median.
    	fprintf(stdout, "\nThe median of the numbers is %d.\nThis completes the task #3 of the Assignment.\n", medianValue);
    }
    else
    {			//Parent calling mean()
    	int value = mean(length, pt);
	//Parent printing the results of mean.
    	fprintf(stdout, "\nThe mean of the numbers is %d.\nThis completes the task #2 of the Assignment.\n", value );
    }
    return 0;
}
