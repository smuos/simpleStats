#include <stdlib.h>
#include <stdio.h>
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

//Calculate mean
float mean(int* list, int length) {
    float me = 0;//the return value for mean functon
    int counter;//number of elements
    for (counter = 0; counter < length; counter++) {
        me = me + list[counter];//add all numbers
    }
    me = me/length;//calculate the mean, easy
    return me;
}

//Calculate median
float median(int* list, int length) {
    /*There are two situations for median number.
      First situation is when the length is an even number,
      the mean of (length/2)th and (length/2+1)th numbers is the median.
      Second situation is when the length is an odd number,
      the median is (length/2)th number. 
    */
    float med;//the return value for median
    //Length is an even number
    if (length%2==0) {
	med = (list[length/2-1] + list[length/2])/2.0;
    }

    //Length is an odd number
    else {
    med = list[(length+1)/2-1];
    }
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
//#if debug
    fprintf(stderr, "%s: DEBUG: %d numbers were passed.\n", argv[0], length);
//#endif

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
    int rc  = fork();//slice off another process
    if (rc < 0) {
	fprintf(stderr,"Fork failed\n");
        exit(1);
    }
    else if (rc == 0) {
   	 fprintf(stdout, "The mean is %.1f\n", mean(pt,length));
    }
    else if (rc > 0) {
	 wait(NULL);//wait for the child end
	 fprintf(stdout, "The median is %.1f\n", median(pt,length));
    }
    return 0;
}
