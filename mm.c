#include <stdlib.h>
#include <stdio.h>

#define debug 0

float mean(int length, int *pt) {
    int i, total=0;
    for(i=0; i<length; i++) {
        total=total+pt[i];
    }
    return ((float)total/length);
}

float median(int length, int *pt) {
    if(length%2==1) return pt[length/2];
    else {
        int *pt2;
        if((pt2 = malloc(2*sizeof(int)))==NULL) {
            fprintf(stderr, "Could not allocate memory.\n");
        }
        pt2[0] = pt[length/2-1];
        pt2[1] = pt[length/2];
        return mean(2, pt2);
    }
}

// Comparison function for qsort()
int numcmp (const void *a, const void *b) {
    int x = *((int*) a);
    int y = *((int*) b);
    if (x > y) return 1;
    if (x < y) return -1;
    return 0;
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
    int rc = fork();
    if (rc == -1) {
        fprintf(stdout, "Could not create another process.\n");
        exit(0);
    }
    else if (rc == 0) {
    fprintf(stdout, "\nMedian: %.2f", median(length, pt));
    }
    else if (rc > 0) {
        int wc = wait(NULL); //is child finished?
        fprintf(stdout, "\nMean: %.2f", mean(length, pt));
    }
    fprintf(stdout, "\n%s: FIN. (pid:%d)\n", argv[0], getpid());

    return 0;
}
