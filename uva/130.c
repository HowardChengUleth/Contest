#include <stdio.h>
#include <assert.h>

#define MAX_N 100

int main(void)
{
  int n, m, k, i, j, n1, n2;
  int circle[MAX_N];

  while (scanf("%d %d", &n, &k) == 2 &&
	 !(n == 0 && k == 0)) {
    for (i = 0; i < n; i++) {
      circle[i] = i;
    }

    i = 0;
    m = n;
    while (m > 1) {
      /* find next guy to kill */
      n1 = (i + k-1) % m;
      
      /* find the guy to bury him */
      j = 0;
      n2 = n1;
      while (j < k) {
	n2 = (n2 + 1) % m;
	if (n2 != n1) {
	  j++;
	}
      }
      assert(n1 != n2);
      
      /* put n2 into n1, shift the rest down */
      circle[n1] = circle[n2];
      for (j = n2; j < m-1; j++) {
	circle[j] = circle[j+1];
      }
      m--;
      if (n1 > n2) {
	i = n1 % m;
      } else {
	i = (n1+1) % m;
      }
    }
    printf("%d\n", (n - circle[0]) % n + 1);
  }
  return 0;
}
