/*
 * We do this by a recurrence relation (and then memorizing the results
 * to avoid precomputation).
 *
 */

#include <stdio.h>

double ans[101][101][100];

double compute(int n, int m, int k)
{
  if (ans[n][m][k] >= 1e-8) {
    /* already computed */
    return ans[n][m][k];
  }
  if (m == 0) {
    /* no long stick, so we can only win if we are the last person */
    return (ans[n][m][k] = (k == n-1) ? 1.0 : 0.0);
  }
    
  if (k) {
    /* the first person picks a short straw, he is out */
    ans[n][m][k] = (double)(n-1)/(n-1+m) * compute(n-1, m, k-1);
    
    /* the first person picks a long straw, he is still in, move him to the
       back */
    ans[n][m][k] += (double)m/(n-1+m) * compute(n, m-1, k-1);
  } else {
    /* I have to pick a long straw, then move to the back of the line */
    ans[n][m][k] = (double)m/(n-1+m) * compute(n, m-1, n-1);
  }
  return ans[n][m][k];
}

int main(void)
{
  int cases;
  int m, n, k;

  for (n = 0; n <= 100; n++) {
    for (m = 0; m <= 100; m++) {
      for (k = 0; k < n; k++) {
	ans[n][m][k] = -1;
      }
    }
  }

  scanf("%d", &cases);
  while (cases-- > 0) {
    scanf("%d %d %d", &n, &m, &k);
    printf("%.3f\n", compute(n, m, k)*100);
  }
  return 0;
}
