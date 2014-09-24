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

/*/
 * Takes a pointer to an 
 * array, the length of the array, and the size 
 * of the array elements (double or int),
 * and returns a double, the average of the 
 * elements.
 */
double mean(const void *a, int length, int size){
    double sum = 0.0;
    switch(size){ // What type of array do we have?
        // Add up the elements
        case sizeof(int):
            for (int i = 0; i < length; i++)
                sum += *((int*)(a + i*size));
            break;
        case sizeof(double):
            for (int i = 0; i < length; i++)
                sum += *((double*) (a + i*size));
            break;
        default: // Exit with error on incorrect input
            exit(-1);
    }
   return (double) sum / length; // Return the average
}

/*/ Takes a pointer to a sorted array of ints and the
 * length of the array and returns a double,the median
 * value, or the average of the two median values
 */
double median(const int *a, int length){
    double result;
    if (length % 2 == 0)
        result = (double) (*((int*) (a + length/2) - 1) + *((int*) (a + length/2))) / 2;
    else
        result = *((int*) (a + (length+1)/2 - 1));
    return result;
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
    
    int rc = fork(NULL);
    double m;
    
    // Exit with error if fork() failed
    if (rc < 0)
        exit(-1);
    // the child calculates the median
    else if (rc == 0){
        // Calculate the median
        m = median(pt, length);

        // Print the median:
        fprintf(stdout, "%s: The median is %f \n", argv[0], m);     
        
        // the child is finished
        exit(0);
    }
    //--------- Parent code -----------//
    
    // wait for the child to finish
    wait(NULL);
    
    // Calculate the mean
    m = mean(pt, length, sizeof(int));
        
    // Print the mean:
    fprintf(stdout, "%s: The mean is %f \n", argv[0], m);     

    // Print out sorted numbers
    fprintf(stdout, "%s: Sorted output is: \n", argv[0]);
    for (i=0; i<length; i++) {
        fprintf(stdout, "%d ", pt[i]);
    }
    fprintf(stdout, "\n%s: FIN. \n", argv[0]);

    return 0;
}
