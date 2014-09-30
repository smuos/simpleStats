#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#define debug 0


//Declare variables
double sum=0;

// Comparison function for qsort()
int numcmp (const void *a, const void *b) {
    int x = *((int*) a);
    int y = *((int*) b);
    if (x > y) return 1;
    if (x < y) return -1;
    return 0;
}

// Find mean
double mean(int* num, int size) {
    // Read all numbers
    int i;
    for (i=0; i<=size-1; i++) {
    	//add all numbers
    	sum += num[i];
    }
    // Calculate meas
    int mean = sum / size;
    return mean;	
}

// Find median
int median(int* num, int size) {
    // Declare variable
    int middle;
    double median;
    middle = size / 2.0;
    // If there are even numbers of an array
    if (size % 2) {
    	median = (num[middle]+num[middle+1])/2.0;
    }
    // If array is odd
    else {
    	median = num[middle];
    }
    return median;
}


int main(int argc, char *argv[]) {

    int i, length, *pt;
    
    // Check for prioper usage
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
        return -1;
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
 
    
    // Add fork
    int rc = fork();
    // Fork problem
    if (rc < -1) {
   	fprintf(stderr,"Can't fork!\n");
    }
    // The child should print the median
    else if (rc == 1) {
    	fprintf(stdout, "Hello, I am child, I should print the median");
    	int child = median(pt, length);
    	// Print the median
	fprintf(stdout, "Median is: %d\n", child);
    }
    // The parent should print the mean
    else if (rc == 2){
	wait(NULL);
	fprintf(stdout, "Hello, I am parent, I should print the mean");
    	int parent = mean(pt, length);
        // Print the mean
    	fprintf(stdout, "Mean is: %d\n", parent);
    }
    fprintf(stdout, "\n%s: FIN. \n", argv[0]);
    
    return 0;
}
