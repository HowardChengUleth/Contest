/* @JUDGE_ID: 1102NT 557 C "" */

#include <stdio.h>
#include <assert.h>

#define BOUND (3.0)

double mult(double *num, double *dem, int n, int m)
{
   int i, j;
   double prod = 1.0;
   i = j = 0;
   while (i < n || j < m) {
      if (prod >= BOUND && j < m) {
         prod /= dem[j++];
      } else if (i < n) {
         prod *= num[i++];
      } else {
         assert(j < m);
         prod /= dem[j++];
      }
   }
   return prod;
}

int main(void)
{
  int An, Bn;
  double A[2000], B[2000];
  int N, n, i, k;
  
  scanf("%d", &N);
  while (N-- > 0) {
    scanf("%d", &n);
    An = Bn = 0;
    for (i = 0; i < n-2; i++) {
      B[Bn++] = 2;
    }
    k = (n-2)/2;
    for (i = 1; i <= k; i++) {
      B[Bn++] = i;
      A[An++] = n-2+1-i;
    }
    printf("%.4f\n", 1-mult(A, B, An, Bn));
  }

  return 0;
}
