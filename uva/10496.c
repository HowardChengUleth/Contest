#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int x[11], y[11];
int n;
int best;

int dist(int i, int j)
{
  return abs(x[i]-x[j]) + abs(y[i]-y[j]);  
}

void solve_case(int *perm, int start)
{
  int i, t;
  int sum;
  if (start == n) {
    sum = dist(0, perm[0]) + dist(perm[n-1], 0);
    for (i = 1; i < n; i++) {
      sum += dist(perm[i-1], perm[i]);
    }
    if (sum < best) {
      best = sum;
    }
    return;
  }
  for (i = start; i < n; i++) {
    t = perm[i];
    perm[i] = perm[start];
    perm[start] = t;
    solve_case(perm, start+1);
    t = perm[i];
    perm[i] = perm[start];
    perm[start] = t;
  }
}


int main(void)
{
  int cases;
  int i;
  int perm[10];

  scanf("%d", &cases);
  while (cases-- > 0) {
    scanf("%*d %*d");   /* just ignore the size */
    scanf("%d %d", x, y);
    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
      scanf("%d %d", x+i, y+i);
      perm[i-1] = i;
    }
    best = INT_MAX;
    solve_case(perm, 0);
    printf("The shortest path has length %d\n", best);
  }

  return 0;
}
