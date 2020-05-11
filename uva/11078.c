#include <stdio.h>

int main(void)
{
  int T;
  int n;
  int maxsofar, maxdiff;
  int x, i;

  scanf("%d", &T);
  while (T-- > 0) {
    scanf("%d", &n);

    scanf("%d", &maxsofar);
    for (i = 1; i < n; i++) {
      scanf("%d", &x);
      if (i == 1 || maxdiff < maxsofar - x) {
	maxdiff = maxsofar - x;
      }
      if (maxsofar < x) {
	maxsofar = x;
      }
    }

    printf("%d\n", maxdiff);
  }

  return 0;
}
