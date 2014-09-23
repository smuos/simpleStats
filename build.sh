#/bin/bash

echo "=== Building MMM executable ==="
gcc -Wall -Wextra -o ./bin/mmm ./src/mmm.c
echo "=== Done building executable ==="
