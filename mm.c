#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#define debug 0

//caculate the mean value
int mean(int* ptr, int length) 
{
     int mean=0;//mean value 
 		int i;
     for(i=0; i<length; i++)
	 {
  	 mean+=ptr[i];// sumup      
 	  }
        mean = mean/length;//the mean= sumup/count 
 
     return mean;
 }
 
//caculate the median value
 int median(int* ptr, int length)
{
    /*check the length of arry, if length is even,the median value is the mean of the 2 numbers in the middle. if length is odd, the median value is the number of length/2 +1 */
	 int  md;//md is median value
 
   	 if(length%2!=0)
	{//odd 
 	md= ptr[length/2];
	 }
   	 else
	{
     	 md=(ptr[length/2]+ptr[(length/2)-1])/2; // md is the mean of 2 value in the median
	}
return md; 
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
    int getmean, getmedian;// for mean and median
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
        fprintf(stdout, "%d\n", pt[i]);
    }
    
/******************************add*******************************/
fprintf(stdout, "All the value we calculate will be rundown \n");
int rc=fork();
if(rc<0)//error 
{
 fprintf( stderr, "can not fork, error\n");
  exit(1);
}
else if (rc==0)
{
//run child process
 fprintf(stdout, "I am child (pid: %d)\n", (int) getpid() );//print out the pid
 getmedian = median(pt, length);//get calculate the median
 fprintf(stdout, "the median value is %d \n" ,getmedian); //print out the Child should print the results of median()
}
else 
 {
 int wc=wait(NULL);//Make the parent wait until child has finished before printing results of mean()
 fprintf(stdout, "hello, I am parent of %d (wc: %d) (pid:%d) \n" , rc, wc, (int) getpid());
 getmean= mean(pt, length);  
 fprintf(stdout, " the mean is %d\n", getmean);
 }
   
	return 0;
}
