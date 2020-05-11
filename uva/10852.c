#include <stdio.h>

int prime[10001];
int plist[10001];
int num_p;

int main(void)
{
  int n, k, m, best, best_x;

  for (n = 2; n <= 10000; n++) {
    prime[n] = 1;
  }
  for (n = 2; n <= 10000; n++) {
    if (!prime[n]) continue;
    for (k = 2*n; k <= 10000; k += n) {
      prime[k] = 0;
    }
    plist[num_p++] = n;
  }

  scanf("%d", &m);
  while (m-- > 0) {
    scanf("%d", &n);
    best = n % plist[0];
    best_x = plist[0];
    for (k = 1; k < num_p && plist[k] <= n; k++) {
      if (best < n % plist[k]) {
	best = n % plist[k];
	best_x = plist[k];
      }
    }
    printf("%d\n", best_x);
  }
  
  return 0;
}
