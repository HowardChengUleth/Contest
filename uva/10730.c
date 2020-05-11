/* @JUDGE_ID: 1102NT 10730 C "" */

#include <stdio.h>

int main(void)
{
  int n, i, d;
  int p[10000], inv[10000];
  int bad;

  scanf("%d:", &n);
  while (n > 0) {
    for (i = 0; i < n; i++) {
      scanf("%d", p+i);
      inv[p[i]] = i;
    }

    bad = 0;
    for (i = 0; i < n && !bad; i++) {
      for (d = 1; p[i]+2*d < n && !bad; d++) {
	if ((i < inv[p[i]+d] && inv[p[i]+d] < inv[p[i]+2*d])
	    || (i > inv[p[i]+d] && inv[p[i]+d] > inv[p[i]+2*d])) {
	  bad = 1;
	}
      }
    }

    printf("%s\n", (bad) ? "no" : "yes");

    scanf("%d:", &n);
  }
  return 0;
}
