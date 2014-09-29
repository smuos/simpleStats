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

double mean(int num[], int length){
    double x=0;
    for(int i = 0; i < length; i++){
	x+=num[i];
    }
    return (x/length);
}

double median(int num[], int length){
    double x;
    if(length%2 == 0)
	x=(num[((length-1)/2)-1] + num[((length-1)/2)+1])/2;
    else
	x=num[(length-1)/2];
    return x;
}

int main(int argc, char *argv[]) {

    int i, length, *pt;
    int status = 0;
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

    int rc = fork();
    if(rc == 0){/*This is child process*/
        fprintf(stdout, "\n%.2f: is the median.\n", median(pt, length));
	return 0;    
    }
    else if(rc > 0){
	int wc = wait(&status);
	if(wc > 0)
	{
            fprintf(stdout, "\n%.2f: is the mean.\n", mean(pt, length));
    	}
    }
    fprintf(stdout, "\n%s: FIN. \n", argv[0]);

    return 0;
}
