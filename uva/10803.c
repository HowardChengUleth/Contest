/* @JUDGE_ID: 1102NT 10803 C "" */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_TOWN 100

void solve_case(void)
{
  int n;
  int x[MAX_TOWN], y[MAX_TOWN];
  int i, j, k;
  double G[MAX_TOWN][MAX_TOWN];
  int d2;
  double d;

  scanf("%d", &n);
  for (i = 0; i < n; i++) {
    scanf("%d %d", x+i, y+i);
  }

  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      d2 = (x[i]-x[j])*(x[i]-x[j]) + (y[i]-y[j])*(y[i]-y[j]);
      G[i][j] = (d2 <= 100) ? sqrt(d2) : -1;
    }
  }
  
  for (k = 0; k < n; k++) {
    for (i = 0; i < n; i++) {
      for (j = 0; j < n; j++) {
	if (G[i][k] >= 0 && G[k][j] >= 0) {
	  d = G[i][k] + G[k][j];
	  if (G[i][j] < 0 || d < G[i][j]) {
	    G[i][j] = d;
	  }
	}
      }
    }
  }

  d = 0;
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      if (G[i][j] < 0) {
	printf("Send Kurdy\n");
	return;
      } else if (G[i][j] > d) {
	d = G[i][j];
      }
    }
  }
  printf("%.4f\n", d);
}

int main(void)
{
  int N, i;

  scanf("%d", &N);
  for (i = 0; i < N; i++) {
    printf("Case #%d:\n", i+1);
    solve_case();
    printf("\n");
  }
  return 0;
}

