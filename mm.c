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

int mean(int* list, int length){
    int m=0;//m is the mean that will be calculated then return
    int i;  //a counter

    for (i=0; i<length; i++) {
       m+=list[i];// accumulate all the data in the list string
    }
    m = m/length;//the mean is equal to the total amount divided by how many term

    return (int)m;
}

int median(int* list, int length){
   //medium is the middle letter in the ordered array of numbers
   //if the length is even number,the (mean of length/2 and length/2+1)th one is the medium
   //if the length is odd number, the (length/2)th one is the medium since length is a interger
   //which means it will always roundup

   int* md;//md is for the even number case

   if(length%2!=0){//means there is a remainder = a odd number
	return list[length/2];
   }
   else{
    	if ((md = malloc(length * sizeof(int))) == NULL) {
        	fprintf(stderr, "Could not allocate memory for calculating the medium of even amount of numbers.\n");
   	 }
      	md[0]=list[length/2];
	md[1]=list[length/2-1];

	/*the following part serve testing purposes:	
	int i;//for testing purposes
   	for (i=0; i<length; i++) {
        	fprintf(stdout, "%d ", md[i]);
    	}
	*/
	
	return mean(md,2);
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
    fprintf(stdout, "\nFYI: all the answers will be round down\n");
    int rc = fork(); //slice off another process by fork
    
    if (rc < 0) {//less than 0,or equal -1
	fprintf(stderr, "Unable to fork\n");//the error is printing to the err log not the screen
	exit(1);//exit(1) indicates error occurs
     } else if (rc == 0) {//this is children
	fprintf(stdout, "this is the child(pid:%d) and the median is %d\n",(int) getpid(), median(pt, length));
     } else if (rc > 0) {
	int wc = wait(NULL); //waiting for the child process to end
    	fprintf(stdout, "this is the parent(pid:%d) and I was waitting for process %d to end,\nand also my child pid is %d",(int) getpid(),(int) wc,(int) rc);
	fprintf(stdout, " the mean is %d\n", mean(pt,length));
    	fprintf(stdout, "%s: FIN.\n", argv[0]);
	}

    return 0;
}
