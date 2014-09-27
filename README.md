CSCI3431-Assignment 1
=====================

 > Goal: A simple C program to calculate the mean and median of input numbers.

## Intro

You have been given code that reads numbers as command line arguments and sorts them.
Create a copy of sort.c named mm.c.
Change mm.c to immplement the following features.

- Add a function, mean(),  to mm.c to calculate the mean to 2 decimal places
- Add a function, median(),  to mm.c to calculate the median to 2 decimal places
- Make mm.c fork(), have the parent call mean() and child call median()
- Child should print the results of median()
- Parent should print the results of mean()
- Make the parent wait until child has finished before printing results of mean()

Each feature listed above has a corresponding issue.
Please use [smart commits](https://help.github.com/articles/closing-issues-via-commit-messages) to address each issue. 

## Submission

As before, submit your assignment as a Pull Request.
Please do this before your next lab period.

## Compile

Be sure to compile with `gcc -Wall`

## Usage

```bash
$ ./mm 1 4 9 2 3 1 7 4 8
```
