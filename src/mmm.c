/* strtol example */
#include <stdio.h>      /* printf */
#include <stdlib.h>     /* strtol */

// === Helpers ===
int comp (const void * elem1, const void * elem2)
{
    int f = *((int*)elem1);
    int s = *((int*)elem2);
    if (f > s) return  1;
    if (f < s) return -1;
    return 0;
}

void printNumArray (const int len, const int *arr)
{
  printf("Num Array:\n");
  printf("%ld %ld", sizeof(arr), sizeof(arr[0]));
  // int len=sizeof(arr)/sizeof(arr[0]);
  printf("len: %d\n", len);
  printf("arr: %d\n", *arr);
  for (int i=0; i<len; i++)
  {
    printf("%d\n", arr[i]);
  }
  printf("\n");
  return;
}

// === Main ===
int main (int argc, const char** argv)
{

  // Must have more than 1 argument
  if (argc < 2)
  {
    printf("Please pass in more arguments.\n");
    return 1;
  }

  // printf("Argc: %d\n", argc);
  int len = argc-1;

  // Generate dynamic array with point to dynamic memory
  int *numArr;
  // printf("len: %d\n", len);
  // printf("size: %ld\n", sizeof(numArr[0]));
  numArr = malloc (len * sizeof(numArr[0]));

  // Iterate over each argument and parse to int
  for (int i=0; i<len; i++)
  {
    // printf("%s\n", argv[i+1]);
    // Parse string to integer
    int num = strtol (argv[i+1], NULL, 10);
    numArr[i] = num;
  }

  // printNumArray(len, numArr);

  // Calculate MEAN (average)
  int sum = 0;
  // int len=sizeof(numArr)/sizeof(numArr[0]);
  for (int i=0; i<len; i++)
  {
    sum += numArr[i];
  }
  double mean = sum/len;
  printf("Mean:\t%lf\n",mean);

  // Calculate Median
  // The median is the middle value, so I'll have to rewrite the list in order:
  double median = 0;
  qsort (numArr, len, sizeof(*numArr), comp);
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
  printf("Median:\t%lf\n", median);

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
  printf("Mode:\t%d\n", mode);

  return 0;
}
