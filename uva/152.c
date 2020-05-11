#include <stdio.h>
#include <math.h>

int tree[5001][3];
int hist[10];
int n;

int main(void)
{
  int i, j, k;
  int d, s, dist;

  while (scanf("%d %d %d", tree[n], tree[n]+1, tree[n]+2) == 3 &&
	 (tree[n][0] || tree[n][1] || tree[n][2]))
    n++;

  for (i = 0; i < n; i++) {
    dist = 100;
    for (j = 0; j < n; j++) {
      if (i == j) continue;
      s = 0;
      for (k = 0; k < 3; k++) {
	d = tree[i][k] - tree[j][k];
	s += d*d;
      }
      d = floor(sqrt(s)) + 0.5;
      if (d < dist) {
	dist = d;
      }
    }
    if (dist < 10) {
      hist[dist]++;
    }
  }

  for (i = 0; i < 10; i++) {
    printf("%4d", hist[i]);
  }
  printf("\n");

  return 0;
}
