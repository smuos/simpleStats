#include <stdio.h>
#include <stdlib.h>
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

//mean()
double mean(int* array, int size)
{
	double ret=0;//result for mean
	int ii=0;//cnt

	for(ii=0; ii<size; ii++)
		ret += array[ii];
	
	ret = ret/size;//calc mean

	return ret;
}

//median()
int median(int* array, int size)
{
	int ret=0;//result for median
	
	int halfsize = size/2;
	ret = array[halfsize];//calc median

	return ret;
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
	printf("\n\n");
	
	//add fork()
	printf("Hi stranger! I'm (pid:%d)\n", (int) getpid());
	printf("\n");
    int rc = fork(); //slice off another process
	
    //error case
    if (rc < 0) {
        // Could not cut another process
        fprintf(stderr, "OS too hard, could not cut.\n");
        exit(0);

    //child process
    } else if (rc == 0) {
        printf("Hello, I am child (pid:%d)\n", (int) rc);

		//print median()
		int rtn2 = median(pt, length);
		printf("median: %d\n", rtn2);
		printf("\n");
    
    //parent process
    } else if (rc > 0) {
        wait(NULL); //is child finished?
        printf("Hello, I am parent (pid:%d)\n", (int) rc);
		
		//print mean()
		double rtn1 = mean(pt, length);
		printf("mean: %f\n", rtn1);
	    fprintf(stdout, "\n%s: FIN. \n", argv[0]);	
    }
		
    return 0;
}
