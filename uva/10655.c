/* @JUDGE_ID: 1102NT 10655 C "" */

#include <stdio.h>

/* Use the formula:

   (a+b) * (a^n + b^n) = (a^(n+1) + b^(n+1)) + a*b*(a^(n-1) + b^(n-1))

   In other words, if x[n] = a^n + b^n, then

   x[n+1] = (a+b) * x[n] - (a*b) * x[n-1]

   This is a second-order recurrence.  To compute it quickly, look at the
   matrix formulation:

   [ a+b    -a*b ] [  x[n]  ]  =  [ x[n+1] ]
   [  1       0  ] [ x[n-1] ]     [  x[n]  ]

   So we can compute x[n] by:

   [ a+b    -a*b ]n-1  [ x[1] ]   =  [  x[n]  ]
   [  1       0  ]     [ x[0] ]      [ x[n-1] ]

   Do it quickly by fast exponentiation

*/

void mult(long long A[2][2], long long B[2][2], long long C[2][2])
{
  C[0][0] = A[0][0]*B[0][0] + A[0][1]*B[1][0];
  C[0][1] = A[0][0]*B[0][1] + A[0][1]*B[1][1];
  C[1][0] = A[1][0]*B[0][0] + A[1][1]*B[1][0];
  C[1][1] = A[1][0]*B[0][1] + A[1][1]*B[1][1];
}

void power(long long A[2][2], int n)
{
  long long res[2][2], x[2][2], t[2][2];
  int i, j;

  for (i = 0; i < 2; i++) {
    for (j = 0; j < 2; j++) {
      res[i][j] = (i == j);
      x[i][j] = A[i][j];
    }
  }

  while (n > 0) {
    if (n & 0x01) {
      n--;
      mult(res, x, t);
      for (i = 0; i < 2; i++) {
	for (j = 0; j < 2; j++) {
	  res[i][j] = t[i][j];
	}
      }
    } else {
      n >>= 1;
      mult(x, x, t);
      for (i = 0; i < 2; i++) {
	for (j = 0; j < 2; j++) {
	  x[i][j] = t[i][j];
	}
      }
    }
  }
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 2; j++) {
      A[i][j] = res[i][j];
    }
  }
}

int main(void)
{
  int ab, apb, n, i;
  long long A[2][2];

  while (scanf("%d %d %d", &apb, &ab, &n) == 3) {
    if (n == 0) {
      printf("2\n");
      continue;
    }
    A[0][0] = apb;  A[0][1] = -ab;
    A[1][0] = 1;    A[1][1] = 0;

    power(A, n-1);

    printf("%lld\n", A[0][0] * apb + A[0][1] * 2);
  }

  return 0;
}
