#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/types.h>


#define debug 0
#define SUCCESS  0 //changed from 1 to 0
#define FAILURE -1 //changed from 0 to -1


// Comparison function for qsort()
int numcmp (const void *a, const void *b) {
    int x = *((int*) a);
    int y = *((int*) b);
    if (x > y) return 1;
    if (x < y) return -1;
    return 0;
}

float mean(int nums[], int size)	//mean function for calculation the mean of an array of float numbers
{
  	float sum=0;
    for (int i = 0; i <=size-1; i++)
    {
		sum +=nums[i];
    }

   	return sum/size;
}

float median(int nums[], int size)	//median function for calculation the mean of an array of float numbers
{
  	if(size%2==0)return (nums[(size/2)-1]+nums[size/2])/2;	//if the array has an even number of integers, we calculate the mean of two numbers in the middle
  	else return nums[size/2];
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
	
	//fork added below, copied from the first lab
	  int rc = fork(); //slice off another process
	  if (rc == -1) { //fork() returns -1, exit with error message.
		// Could not cut another process
		fprintf(stdout, "OS too hard, could not cut.\n");
		exit(FAILURE);
	  } else if (rc == 0) { //when fork() returns 0, exit with success message.
		float medianV = median(pt,length);	//child calls median
		fprintf(stdout, "The median value is: %.2f: ", medianV);
	  } else { //when fork() returns others nums, create new child 
		float meanV = mean(pt,length);	//parent calls mean
		fprintf(stdout, "The mean value is: %.2f: ", meanV);
	  }
	  return SUCCESS;
}
