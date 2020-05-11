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

void factor(int n) {
  long long p;
  int ans = 1;
  int count;
  int orig = n;

  if (n == 0 || n == 1) {
    /* must be 1 in this problem */
    printf("%d %d\n", orig, 1);
    return;
  }
  if (n < 0) {
    /* not possible in this problem */
    n *= -1;
    printf("-1\n");
  }

  count = 0;
  while (n % 2 == 0) {
    n/=2;
    count++;
  }
  ans *= 2*count + 1;

  for (p = 3; p*p <= n; p += 2) {
    count = 0;
    while (n % p == 0) {
      n /= p;
      count++;
    }
    ans *= 2*count+1;
  }
  if (n > 1) {
    ans *= 3;
  }

  ans -= ans/2;
  printf("%d %d\n", orig, ans);
}

int main(void) {
  int n;
  while(scanf("%d", &n) == 1) {
    if(!n)
      break;
    factor(n);
  }
  return 0;
}










