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

//Issues#2: Add a function, mean(),to mm.c to calculate the mean
double mean (int *num, int len){

  double sum = 0, mean = 0;

  //using a for loop to add up all the values in input numbers
  int i;

  for( i = 0; i<len ;i++){
    sum = sum + num[i];
  }

  //Find the mean
  mean = sum / len;

  return mean;
}

//Issues #3 Add a function, median(),to mm.c calculate the median
double median(int *num, int len){
  
  double median;
  //If the array length is an even number
  if(len%2==0){
    median = (num[len/2]+num[len/2+1])/2.0;
  }
  //Otherwise the array length is a odd number
  else{
    median = num[(len+1)/2];
  }
  return median;
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
    
    //Issues #4 make mm.c fork(),have the parent call mean() and child call median()
    int rc = fork();
    //Check the rc value, if it return -1 means fork function fail
    if(rc == -1){
      fprintf(stderr,"Fork failed! No child!\n");
    }else if (rc == 0){
      //if rc equal to 0 which means fork succeed,the child is processing
      //let child process print the result of median()
      //Issues#5 Child process should print the results of median()
      fprintf(stdout, "This is child processing!\n ");
      fprintf(stdout, "The median value is %lf.\n",median(pt,length));
    }else if (rc ==1){
      //if rc equal to 1 means fork succeed, the parent is processing
      //let parent process print the result of mean()
      //Issues#6 Parent process should print the results of mean()
      fprintf(stdout,"This is parent processing!\n");
      fprintf(stdout, "The mean value is %lf.\n",mean(pt,length));
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

    return 0;
}
