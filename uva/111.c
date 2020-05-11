/* @JUDGE_ID: 1102NT 111 C "" */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_N 20

int score(int n, int *order, int *response)
{
  int best[MAX_N+1][MAX_N+1];
  int i, j;
  
  for (i = 0; i <= n; i++) {
    best[i][0] = best[0][i] = 0;
  }

  for (i = 1; i <= n; i++) {
    for (j = 1; j <= n; j++) {
      if (order[i-1] == response[j-1]) {
	best[i][j] = best[i-1][j-1] + 1;
      } else {
	best[i][j] = best[i-1][j];
	if (best[i][j] < best[i][j-1]) {
	  best[i][j] = best[i][j-1];
	}
      }
    }
  }

  return best[n][n];
}

int main(void)
{
  int n, i, t;
  int order[MAX_N], response[MAX_N];
  
  scanf("%d", &n);
  assert(2 <= n && n <= 20);

  for (i = 0; i < n; i++) {
    scanf("%d", &t);
    order[t-1] = i;
  }

  while (scanf("%d", &t) == 1) {
    response[t-1] = 0;
    for (i = 1; i < n; i++) {
      scanf("%d", &t);
      response[t-1] = i;
    } 
    printf("%d\n", score(n, order, response));
  }

  return 0;
}
