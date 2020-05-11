/*
 * Prime Factorization
 *
 * Author: Ethan Kim
 * Complexity: O(sqrt(n))
 *
 * Takes an integer and writes out the prime factorization in
 * ascending order. Prints -1 first, when given a negative integer.
 *
 * Note: you can change this code to store the factors in an array or process
 * the factors in other ways.
 * 
 * Also, this code works for all integers even on INT_MIN (note that negating
 * INT_MIN does nothing, but it still works because INT_MIN is a power of 2).
 *
 */

#include <stdio.h>

int factors(int n) {
  int count = 0;
  long long p;

  if (n == 0 || n == 1) {
    return count;
  }

  while (n % 2 == 0) {
    n/=2;
    count = 1;
  }

  for (p = 3; p*p <= n; p += 2) {
    if (n % p == 0) {
      count++;

      while (n % p == 0) {
	n /= p;
      }
    }
  }

  if (n>1) {
    count++;
  }
  return count;
}

int main(void) {
  int p;
  while(scanf("%d", &p) == 1 && p) {
    printf("%d : %d\n", p, factors(p));
  }
  return 0;
}










