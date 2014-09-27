#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#define debug 0

// Function declaration
float mean(int length, int pt[]);
float median(int length, int pt[]);

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

    // Print out numbers message
    fprintf(stdout, "%s: Sorted output is: \n", argv[0]);

    // Fork the process
    int rc = fork();
    
    // Fork failed
    if (rc < 0) {
    	fprintf(stderr, "Fork failed!\n");
 	exit(1);
    // The child process
    } else if (rc == 0) {
	// print out numbers
	for (i = 0; i < length; i++) {
	   fprintf(stdout, "%d ", pt[i]);
	}
	//print out the median
	fprintf(stdout, "\nThe median is: %f", median(length, pt));;
    // The parent process
    } else {
	wait(NULL);
	//print out the mean
	fprintf(stdout, "\nThe mean is: %f", mean(length, pt));
	fprintf(stdout, "\n%s: FIN. \n", argv[0]);
    }

    return 0;
}

float mean(int length, int pt[])
{
    int i, sum;
    float mean;
    sum = 0;
    for (i = 0; i < length; i++) {
	sum += pt[i];
    }
    mean = sum/(float)length;
    return mean;
}

float median(int length, int pt[])
{
    float median;
    if (length % 2 == 0)
        median = (float)(pt[length/2 - 1] + pt[length/2])/2;
    else
	median = pt[length/2];
    return median;
}
