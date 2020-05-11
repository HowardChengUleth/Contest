/*
 * If we form a linear system of equations with a0, a1, ..., a(n+1) as 
 * unknowns, we get something like this (for n = 2):
 *
 *     [  1     0      0     0  ] [ a0 ]   [ a0 ]
 *     [ 1/2   -1     1/2    0  ] [ a1 ] = [ c1 ]
 *     [  0    1/2    -1    1/2 ] [ a2 ]   [ c2 ]
 *     [  0     0      0     1  ] [ a3 ]   [ a3 ]
 *
 * so we start from the last equation and last column and keep eliminating
 * backwards until we reach the second equation and second column.  Then
 * we can easily remove a0 to get the answer.  The matrix is sparse so
 * we can (and have to) do better than O(n^3).  This is basically a 
 * tridiagonal solver.
 *
 * We will assume that the matrix is:
 *
 *          a0 c0
 *          b1 a1 c1
 *            ....
 *                bn  an   cn
 *                   bn+1 an+1
 *
 */


#include <stdio.h>

int main(void)
{
  int cases;
  int n;
  double a[3002], b[3002], c[3002], rhs[3002], w[3002], v[3002], z[3002],
    y[3002];
  int i;

  scanf("%d", &cases);
  while (cases-- > 0) {
    scanf("%d", &n);
    scanf("%lf %lf", rhs+0, rhs+n+1);
    for (i = 1; i <= n; i++) {
      scanf("%lf", rhs+i);
    }
    a[0] = a[n+1] = 1;
    b[0] = b[n+1] = 0;
    c[0] = c[n+1] = 0;
    for (i = 1; i <= n; i++) {
      a[i] = -1;
      b[i] = c[i] = 0.5;
    }
    w[0] = a[0];
    v[0] = c[0]/w[0];
    z[0] = rhs[0]/w[0];
    for (i = 1; i <= n+1; i++) {
      w[i] = a[i] - b[i]*v[i-1];
      v[i] = c[i]/w[i];
      z[i] = (rhs[i] - b[i]*z[i-1])/w[i];
    }
    y[n+1] = z[n+1];
    for (i = n; i >= 0; i--) {
      y[i] = z[i] - v[i]*y[i+1];
    }
    printf("%.2f\n", y[1]);


    if (cases) {
      printf("\n");
    }
  }

  return 0;
}
