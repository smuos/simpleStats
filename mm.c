#include <stdlib.h>
#include <stdio.h>

#define debug 0

// Comparison function for qsort()
int numcmp (const void *a, const void *b) {
    int x = *((int*) a);
    int y = *((int*) b);
    if (x > y) return 1;
    if (x < y) return -1;
    return 0;
}

// function to calculate mean
float mean(const int* a, int n){
  float avg =0;
  int i;

  for(i=0; i<n ; i++)
    avg += a[i];

  avg /= n;

  return avg;
}

// function to calculate median
float median(const int* a, int n){
  float med = 0;

  if(n % 2 == 0)
    med = ( a[n/2-1] + a[n/2] ) / 2.0;
  else
    med = a[n/2];

  return med;
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

    fprintf(stdout, "\n");
    fflush(stdout);

    int rc = fork();
    float medianVal, meanVal;

    if (rc < 0) { // fork failed; exit
      fprintf(stderr, "fork failed\n");
      exit(1);
    } else if (rc == 0) { //child (new process)
      medianVal = median(pt, length);
      fprintf(stdout, "median=%.2f\n", medianVal);
    } else { // parent goes down this path (main)
      meanVal = mean(pt, length);
      fprintf(stdout, "\n%s: FIN. \n", argv[0]);
    }

    return 0;
}
