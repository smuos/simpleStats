#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define debug 0
#define FAILED 1

// Declare Function
int numcmp (const void *a, const void *b);
float mean(int *num, int length);
float median(int *num, int length);

// Comparison function for qsort()
int numcmp (const void *a, const void *b) {
    int x = *((int*) a);
    int y = *((int*) b);
    if (x > y) return 1;
    if (x < y) return -1;
    return 0;
}

//Mean functiont that outputs mean of an array
float mean(int *num, int length) {
  // Initialization of vars
  // sum -> sum of ints of array
  // i -> num used for doing iteation
  float sum = 0;
  int i;
  // For loop to add every number to sum
  for(i=0; i<length;i++){
    sum += num[i];
  }
  // Return mean
  return sum/length;
}

// Median function that outputs median
float median(int *num, int length){
  // If the length of array is even
  if (length%2==0){
    //return the average number between two median numbers
    return (num[length/2-1]+num[length/2])/(float)2;
  // If the length of array is odd 
  }else{
  // Return the median
    return num[length/2+1];
  }
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
    
    // Initilaztion fork() for process
    int rc = fork();

    // If there is no arugment
    if (rc < 0){
      fprintf(stderr, "Fork Failed %s\n", argv[0]);
      exit(FAILED);
    // If the process is child
    } else if (rc == 0){
      fprintf(stdout, "This is child process(pid:%d)\n", (int)getpid());
      fprintf(stdout, "The median is: %f", median(pt, length));
    // If the process is parent
    } else if (rc > 0){
      fprintf(stdout, "\nThis is parent prcesss(pid:%d)\n", (int)getpid());
      fprintf(stdout, "The mean is: %f\n", mean(pt, length));
      fprintf(stdout, "%s: FIN. \n",argv[0]);
    }

    return 0;
   
}
