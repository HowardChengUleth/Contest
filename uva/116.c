/* @JUDGE_ID: 1102NT 116 C "" */

#include <stdio.h>

int board[10][100];
int m, n;

int read_case(void)
{
  int i, j;
  if (scanf("%d %d", &m, &n) != 2) {
    return 0;
  } 

  for (i = 0; i < m; i++) {
    for (j = 0; j < n; j++) {
      scanf("%d", &board[i][j]);
    }
  }

  return 1;
}

void solve_case(void)
{
  int dist[10][100], succ[10][100];
  int i, j, k, t;
  
  /* do the last column */
  for (i = 0; i < m; i++) {
    dist[i][n-1] = board[i][n-1];
    succ[i][n-1] = -1;
  }

  /* work backward */
  for (j = n-2; j >= 0; j--) {
    for (i = 0; i < m; i++) {
      dist[i][j] = board[i][j] + dist[i][j+1];
      succ[i][j] = i;
      
      k = (i+1)%m;
      t = board[i][j] + dist[k][j+1];
      if (t < dist[i][j] || (t == dist[i][j] && k < succ[i][j])) {
	dist[i][j] = t;
	succ[i][j] = k;
      }
      
      k = (i+m-1)%m;
      t = board[i][j] + dist[k][j+1];
      if (t < dist[i][j] || (t == dist[i][j] && k < succ[i][j])) {
	dist[i][j] = t;
	succ[i][j] = k;
      }
    }
  }

  /* now find the best in column 1 */
  k = 0;
  for (i = 1; i < m; i++) {
    if (dist[i][0] < dist[k][0]) {
      k = i;
    }
  }
  i = k;
  for (j = 0; j < n; j++) {
    printf("%d%s", i+1, (j < n-1) ? " " : "\n");
    i = succ[i][j];
  }
  printf("%d\n", dist[k][0]);
}

int main(void)
{
  while (read_case()) {
    solve_case();
  }
  return 0;
}
