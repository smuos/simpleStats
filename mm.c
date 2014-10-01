#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#define debug 0
#define SUCCESS 0
#define FAILURE -1

// Comparison function for qsort()
int numcmp (const void *a, const void *b) {
    int x = *((int*) a);
    int y = *((int*) b);
    if (x > y) return 1;
    if (x < y) return -1;
    return 0;
}

// mean()
//    int n,  the length of the list
//    char *list[], command line argument. Data starts at index 1. 
double  mean(int n, char *list[]) {
    int sum = 0;
    int i;
    for(i = 1; i < n; i++) {
        sum +=  atoi(list[i]);
    }
    return (double) sum / (double)(n-1);
}

// median()
//    int n, number of elements in list.
//    int *list, pointer to first element of a SORTED list.
double median(int n , int *list) {
    if ((n-1) % 2 != 0) {
        return (double) list[(n-1)/2];
    }
    else {
        return ((double) list[((n-1)/2)-1] + (double) list[((n-1)/2)]) / 2.0;
    }
}

int main(int argc, char *argv[]) {

    int i, length, *pt;

    // Check for proper usage
    if (argc < 2) {
        fprintf(stderr, "%s: Aborting, not enough arguments.\n", argv[0]);
        return FAILURE;
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

    // Print out results
    fprintf(stdout, "%s results: \n", argv[0]);

    int rc = fork();

    if (rc < 0) {
        fprintf(stderr,"%s aborting: Could not fork\n", argv[0]);
        return FAILURE;
    }

    if (rc == 0) {
        // Child code.
        fprintf(stdout, "Median = %f\n", median(argc,pt));
#if debug
    fprintf(stdout, "%s: DEBUG: rc = %d, PID = %d\n",argv[0],rc,getpid());
#endif
    }

    if  (rc > 0) {
        //parent code.
        wait(NULL); // wait until child is finished.
        fprintf(stdout,"Mean = %f\n", mean(argc,argv));
#if debug
    fprintf(stdout, "%s: DEBUG: rc = %d, PID = %d\n", argv[0],rc,getpid());
#endif
    }
    return SUCCESS;
}
