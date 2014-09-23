CSCI3431-Assignment 1
=====================

 > Goal: A simple C program to calculate the mean and median of input numbers.

## Intro

You have been given code that reads numbers as command line arguments and sorts them.
Create a copy of sort.c named mm.c.
Change mm.c to immplement the following features.

- Add a function, mean(),  to mm.c to calculate the mean
- Add a function, median(),  to mm.c to calculate the median
- Make mm.c fork(), have the parent call mean() and child call median()
- Child should print the results of median()
- Parent should print the results of mean()
- Make the parent wait until child has finished before printing results of mean()

Each feature listed above has a corresponding issue.
Please use [smart commits](https://help.github.com/articles/closing-issues-via-commit-messages) to address each issue. 

## Compile

Be sure to compile with `gcc -Wall`

## Usage

```bash
$./sort 1 4 9 2 3 1 7 4 8
./sort: Sorted output is:
1 1 2 3 4 4 7 8 9
```
