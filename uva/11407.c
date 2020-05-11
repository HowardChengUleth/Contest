#include <stdio.h>
#include <math.h>

int ans[10001];

void precompute(void)
{
  int n, r, t;

  ans[1] = 1;
  for (n = 2; n <= 10000; n++) {
    r = (int)floor(sqrt(n)+0.5);
    if (r*r == n) {
      ans[n] = 1;
      continue;
    }

    ans[n] = ans[1] + ans[n-1];
    for (r = 2; r <= n-1; r++) {
      t = ans[r] + ans[n-r];
      if (t < ans[n]) {
	ans[n] = t;
      }
    }
  }
}

int main(void)
{
  int t, n;

  precompute();

  scanf("%d", &t);
  while (t-- > 0) {
    scanf("%d", &n);
    printf("%d\n", ans[n]);
  }

  return 0;
}
