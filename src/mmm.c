/* strtol example */
#include <stdio.h>      /* printf */
#include <stdlib.h>     /* strtol */
#include <unistd.h>

// === Helpers ===
/**
Compare function used with qsort
Source code referenced from http://stackoverflow.com/a/1788048/2578205

@param elem1 First item in comparison.
@param elem2 Second item in comparison.
@return integer representing comparison between elem1 and elem2
*/
int comp (const void * elem1, const void * elem2)
{
  // Cast void* to int
  int f = *((int*)elem1);
  int s = *((int*)elem2);
  /*
  // To elaborate
  // Cast void* to int*
  int *pointer = (int *)voidPtr;
  // Derefernce pointer to int value
  int val = *(pointer);
  */
  if (f > s) return  1;
  if (f < s) return -1;
  return 0;
}

/**
Print Number Array

@param len Length of array.
@param arr The array.
@return void
*/
void printNumArray (const int len, const int *arr)
{
  printf("Num Array:\n");
  printf("%ld %ld", sizeof(arr), sizeof(arr[0]));
  // int len=sizeof(arr)/sizeof(arr[0]);
  printf("len: %d\n", len);
  printf("arr: %d\n", *arr);
  for (int i=0; i<len; i++)
  {
    printf("%d: %d\n", i, arr[i]);
  }
  printf("\n");
  return;
}

/**
Mean calculation helper.

@param len Length of array.
@param numArr The number array.
@return The calculated mean of numArray.
*/
double mean(const int len, const int *numArr)
{
  // Calculate MEAN (average)
  int sum = 0;
  // int len=sizeof(numArr)/sizeof(numArr[0]);
  for (int i=0; i<len; i++)
  {
    sum += numArr[i];
  }
  return sum/len;
}

/**
Mode calculation helper.

@param len Length of array.
@param numArr The number array, already sorted array.
@return The calculated mode of numArray.
*/
int mode(const int len, const int *numArr)
{
  // Calculate Mode
  // The mode is the number that is repeated more often than any other, so 13 is the mode.
  // Note: Some source code below
  // referenced from http://stackoverflow.com/a/19920690/2578205
  // Setup
  int number = numArr[0];
  int mode = number;
  int count = 1;
  int countMode = 1;
  // Iterate to find the mode
  for (int i=1; i<len; i++)
  {
        if (numArr[i] == number)
        { // count occurrences of the current number
           countMode++;
        }
        else
        { // now this is a different number
              if (count > countMode)
              {
                    countMode = count; // mode is the biggest ocurrences
                    mode = number;
              }
             count = 1; // reset count for the new number
             number = numArr[i];
    }
  }
  return mode;
}

/**
Median calculation helper.

@param len Length of array.
@param numArr The number array, already sorted.
@return The calculated median of numArray.
*/
double median(const int len, const int*numArr)
{
  // Calculate Median
  // The median is the middle value, so I'll have to rewrite the list in order:
  double median = 0;
  // printNumArray(len, numArr);
  int middle = (int) len/2;
  // Check if even
  if (len % 2 == 0)
  {
    // is even
    // when there are an even amount of numbers things are slightly different.
    // In that case we need to find the middle pair of numbers,
    // and then find the value that would be half way between them. This is easily done by adding them together and dividing by two.
    int a = numArr[middle];
    int b = numArr[middle+1];
    // printf("%d \t %d\n", a,b);
    median = (a+b)/2;
  } else {
    // is odd
    median = numArr[middle];
  }
  return median;
}

// === Main ===
/**
Start of program

@param argc argument count
@param argv argument vector
@return an integer indicating success or failure.
*/
int main (int argc, const char** argv)
{

  // Check for proper usage
  if (argc < 2) {
      fprintf(stderr, "%s: Aborting, not enough arguments.\n", argv[0]);
      return (-1);
  }

  int len = argc-1;

  // Generate dynamic array with point to dynamic memory
  int *numArr;
  numArr = malloc (len * sizeof(numArr[0]));

  // Iterate over each argument and parse to int
  for (int i=0; i<len; i++)
  {
    // Parse string to integer
    int num = strtol (argv[i+1], NULL, 10);
    // and store in array
    numArr[i] = num;
  }

  // Fork and create a child process
  int rc = fork();

  // Run different code based on if there was an error,
  // it is the parent, or is the child.
  if (rc < -1) {
      // Error: Could not cut another process
      fprintf(stdout, "OS too hard, could not cut.\n");
      exit(0);
  } else if (rc == 0) {
      // Is child

      // Sort array first
      qsort (numArr, len, sizeof(*numArr), comp);
      // Median
      printf("Median:\t%lf\n", median(len, numArr));
      // Mode
      printf("Mode:\t%d\n", mode(len, numArr));

  } else if (rc > 0) {
      // Is Parent
      wait(NULL); //is child finished?
      // Mean
      printf("Mean:\t%lf\n",mean(len, numArr));
  }

  return 0;
}
