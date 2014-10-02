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

// Mean function
double mean (int pt[] ,int length)
{
    int i;
    double avg;
    double sum = 0;
    for (i = 0; i <= length; i++)
    {
        sum += pt[i];
    }
    avg = sum/length;
    return avg;
}

// Median function
double median (int pt[],int length)
{
    double first, second, final;
    if (length%2 == 0)
    {
       first =  pt[length/2];
       second = pt[(length/2) + 1];
       final = (first + second)/2;
       return final;
    }
    else
    {
        final = pt[length/2];
        return final;
    }
}

int main(int argc, char *argv[]) {

    int i, length, *pt;
    double meancomp, mediancomp;
    
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
    
    // Creating a fork process
    int frk = fork();
   
    if (frk < 0)
    {
       fprintf(stdout, "Something is wrong");
       exit(0);
    }

    if(frk == 0) // child
    {
        // Find the median of the numbers
        mediancomp = median(pt,length);    
        fprintf(stdout,"\nThe median of the numbers are: %f",mediancomp);
     }
    
    if (frk > 0) //parent
    {
         int wc = wait(NULL);
         // Find the mean of the numbers
         meancomp =  mean(pt,length);	
         fprintf(stdout,"\nThe mean of the numbers are: %f",meancomp);
        

         // Print out numbers
         fprintf(stdout, "\nSorted output is: \n");
         for (i=0; i<length; i++) {
         fprintf(stdout, "%d ", pt[i]);
         }
         fprintf(stdout, "\nFIN. \n");
    }
    return 0;
}
