/* @JUDGE_ID: 1102NT 366 C "" */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_DIM 20
#define MAX_LAYER 200

int cuts[MAX_DIM+1][MAX_DIM+1][MAX_LAYER];
char set[MAX_DIM+1][MAX_DIM+1][MAX_LAYER];

int max(int a, int b)
{
  return (a > b) ? a : b;
}

int min(int a, int b)
{
  return (a < b) ? a : b;
}

int min_cuts(int m, int n, int layers)
{
  int best;
  int i, j;
  int p1, p2;
  int res1, res2;
  int half;

  if (set[m][n][layers]) {
    return cuts[m][n][layers];
  }

  best = m*n;

  /* try cutting in the m direction */
  half = (m-1)/2;
  if (m == 2 || (m % 2 == 0 && half+1 <= m-1)) {
    half++;
  }
  for (i = 1, p1 = m-i; i <= half; i++, p1--) {
    if (layers > 1) {
      for (j = 1, p2 = layers-j; j < layers; j++, p2--) {
	res1 = min_cuts(i, n, j);
	if (res1 + 1 < best) {
	  res2 = min_cuts(p1, n, p2);
	  best = min(best, max(res1, res2) + 1);
	}
      }
    } else {
      res1 = min_cuts(i, n, 1);
      if (res1 + 1 < best) {
	res2 = min_cuts(p1, n, 1);
	best = min(best, res1+res2+1);
      }
    }
  }

  /* try cutting in the n direction */
  half = (n-1)/2;
  if (n == 2 || (n % 2 == 0 && half+1 <= n-1)) {
    half++;
  }
  for (i = 1, p1 = n-i; i <= half; i++, p1--) {
    if (layers > 1) {
      for (j = 1, p2 = layers-j; j < layers; j++, p2--) {
	res1 = min_cuts(m, i, j);
	if (res1 + 1 < best) {
	  res2 = min_cuts(m, p1, p2);
	  best = min(best, max(res1, res2) + 1);
	}
      }
    } else {
      res1 = min_cuts(m, i, 1);
      if (res1 + 1 < best) {
	res2 = min_cuts(m, p1, 1);
	best = min(best, res1+res2+1);
      }
    }
  }

  cuts[m][n][layers] = cuts[n][m][layers] = best;
  set[m][n][layers] = set[n][m][layers] = 1;
  return best;
}

int main(void)
{
  int layers;
  int m, n;
  int i, j, l;

  for (l = 0; l <= MAX_LAYER; l++) {
    for (i = 0; i <= MAX_DIM; i++) {
      for (j = 0; j <= MAX_DIM; j++) {
	set[i][j][l] = 0;
      }
    }
    set[1][1][l] = 1;
    cuts[1][1][l] = 0;
  }

  while (scanf("%d %d %d", &layers, &m, &n) == 3 && 
         (layers != 0 || m != 0 || n != 0)) {
    printf("%d by %d takes %d cuts\n\n", m, n,
	   min_cuts(m, n, layers));
  }
  return 0;
}





