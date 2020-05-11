/* @JUDGE_ID: 1102NT 412 C "" */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

int A[100];
int n;

int gcd(int a, int b)
{
  int r;

  while (b) {
    r = a % b;
    a = b;
    b = r;
  }
  assert(a >= 0);
  return a;
}

int main(void)
{
  int c, t, i, j;

  while (scanf("%d", &n) == 1 && n > 0) {
    for (i = 0; i < n; i++) {
      scanf("%d", &A[i]);
    }
    c = t = 0;
    for (i = 0; i < n; i++) {
      for (j = i+1; j < n; j++) {
	t++;
	if (gcd(A[i], A[j]) == 1) {
	  c++;
	}
      }
    }

    if (c) {
      printf("%8.6f\n", sqrt(6.0/((double)c/t)));
    } else {
      printf("No estimate for this data set.\n");
    }
  }
  return 0;
}
