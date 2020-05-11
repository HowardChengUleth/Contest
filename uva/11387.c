#include <stdio.h>

void solve(int n)
{
  int edges;
  int k, u, v;

  if (n % 2 || n < 4) {
    printf("Impossible\n");
    return;
  }

  edges = 3*n/2;
  printf("%d\n", edges);
  
  for (k = 1; k <= n; k++) {
    u = k;
    v = (k == n) ? 1 : k+1;
    if (u < v) {
      printf("%d %d\n", u, v);
    } else {
      printf("%d %d\n", v, u);
    }
  }

  for (k = 1; k <= n/2; k++) {
    printf("%d %d\n", k, k+n/2);
  }
}

int main(void)
{
  int n;

  while (scanf("%d", &n) == 1 && n) {
    solve(n);
  }
  return 0;
}
