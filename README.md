# Array-complement
Algorithm generates one int random array, and calculates another special array from the first one.

1. User inputs size of array.
2. Algorithm creates array A and B of this size, and populates A with generated random integers of uniform distribution within some limits.
3. Array B[i] element is calculated to be multiplication of all A elements except A[i].
Calculating process ends up if product to be exceeded limits INT_MAX, INT_MIN, so suggested input limits are not wide.
Algorithm processes cases when one or more zeros in A can happen.
