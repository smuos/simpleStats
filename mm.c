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

// mean value
int mean(int length, int *pt){
    int i;
    double value = 0;
    for(i = 0; i < length; i++){
	value = value + pt[i];
    }
    value = value/length;
    return value;
}

// median value
int median(int length, int *pt){
	int middle;
	if(length % 2 != 0){
		middle = (pt[length/2] +pt[(length/2)+1]) / 2;
	}else{
		middle = pt[length/2];
	}
	return middle;
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
	
	//fork
	int rc = fork(); 
	if (rc < 0) {
	fprintf(stdout, "Cannot fork()\n");
	exit(0);
	} else if (rc == 0) {

	printf("Hello, I am child (pid:%d)\n", (int) rc);
	//find the middle value
	int medianvalue;
	medianvalue = median(length, pt);
	fprintf(stdout, "I'm child and the median value is: %d\n", medianvalue);

	} else{
	int wc = wait(NULL);
	//wait for child
	printf("Waiting the child, I am %d (wc:%d) (pid:%d)\n",
	getpid(), wc, (int) rc);
	// find the mean value.
    int meanvalue; 
    meanvalue = mean(length,pt);
    fprintf(stdout, "I'm parents and the mean value is: %d\n",meanvalue);
	}

    return 0;
}
