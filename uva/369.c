/* @JUDGE_ID: 1102NT 369 C "" */

#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b)
{
   int r;

   while (b) {
      r = a % b;
      a = b;
      b = r;
   }
   return a;
}

unsigned long mult(int *A, int n, int *B, int m)
{
   int i, j, d;
   unsigned long prod;
   int count = 0;
   for (i = 0; i < n; i++) {
      for (j = 0; j < m; j++) {
         d = gcd(A[i], B[j]);
         A[i] /= d;
         B[j] /= d;
      }
   }
   prod = 1UL;
   for (i = 0; i < n; i++) {
      prod *= A[i];
   }

   return prod;
}

unsigned long binom(int n, int m)
{
  int *A, *B;
  int i, k1, k2;
  unsigned long res;

  A = malloc(n*sizeof(int));
  B = malloc(m*sizeof(int));

  k1 = 0;
  for (i = n; i >= n-m+1; i--) {
    A[k1++] = i;
  }
  k2 = 0;
  for (i = m; i >= 1; i--) {
    B[k2++] = i;
  }
  res = mult(A, k1, B, k2);
  free(A);
  free(B);
  return res;
}


int main(void)
{
  int n, m;

  while (scanf("%d %d", &n, &m) == 2 && (n || m)) {
    printf("%d things taken %d at a time is %u exactly.\n", n, m, binom(n, m));
  }
  return 0;
}
