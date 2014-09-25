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

//Function to calculate the mean 
int mean( int *theArray, int arrayLength)
{
	int sumOfArray = 0;
	int i;

	for(i = 0; i < arrayLength; i++){
		sumOfArray = sumOfArray + theArray[i];
	}	

	return sumOfArray / arrayLength;
}//end mean

//the median function
int median(int *theArray, int arrayLength)
{
	int middleNum;
	//even
	if((arrayLength / 2) == 0)
	{

	middleNum = (arrayLength / 2) - 1;

	}
	else
	{
        middleNum = (((arrayLength + 1) / 2) - 1);
	}

	return theArray[middleNum];
}//end median

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

        //fork()
	int rc = fork();
	
	if(rc < 0)
	{
	fprintf(stderr, "%s: Error forking.\n", argv[0]);
        }

	else if(rc == 0)
	{
	//child
        fprintf(stdout, "\n%d ", median(pt, length));
	}
	
	else if (rc > 0)
	{
        //parent
	int waitCode  = wait(NULL);
	fprintf(stdout, "\n%d ", mean(pt, length));
	}




    return 0;
}
