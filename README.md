CSCI3431 - Assignment 1 - MMMExample
===================

> Goal: A simple C program to calculate the mean and median of input numbers.

---

## Intro

You have been given code that reads numbers as command line arguments and sorts them.
Create a copy of `sort.c` named `mm.c`.
Change `mm.c` to implement the following features.

- [x] Add a function, `mean()`,  to `mm.c` to calculate the mean
- [x] Add a function, `median()`,  to `mm.c` to calculate the median
- [x] Make mm.c fork(), have the parent call mean() and child call median()
- [x] Child should print the results of median()
- [x] Parent should print the results of mean()
- [x] Make the parent wait until child has finished before printing results of mean()

Each feature listed above has a corresponding issue.
Please use [smart commits](https://help.github.com/articles/closing-issues-via-commit-messages) to address each issue.

## Compile

```bash
./build.sh
```

## Usage

For example:

```bash
$ ./bin/mmm 13 18 13 14 13 16 14 21 13
Median:	14.000000
Mode:	13
Mean:	15.000000
```
