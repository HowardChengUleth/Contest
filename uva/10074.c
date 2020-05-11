#include <stdio.h>

int A[100][100];
int best_horiz[100][100];
int M, N;

int main(void)
{
  int i, j, k, curr_w;
  int best;

  while (scanf("%d %d", &M, &N) == 2 && (M || N)) {
    for (i = 0; i < M; i++) {
      for (j = 0; j < N; j++) {
	scanf("%d", &A[i][j]);
      }
    }

    best = 0;
    for (i = 0; i < M; i++) {
      best_horiz[i][0] = (A[i][0]) ? 0 : 1;
      if (best_horiz[i][0] > best) {
	best = best_horiz[i][0];
      }
      for (j = 1; j < N; j++) {
	best_horiz[i][j] = (A[i][j]) ? 0 : 1 + best_horiz[i][j-1];
	if (best_horiz[i][j] > best) {
	  best = best_horiz[i][j];
	}
      }
    }

    for (j = 0; j < N; j++) {
      for (i = 1; i < M; i++) {
	if (!(curr_w = best_horiz[i][j])) continue;
	for (k = i-1; k >= 0 && curr_w > 0; k--) {
	  if (best_horiz[k][j] < curr_w) {
	    curr_w = best_horiz[k][j];
	  }
	  if ((i-k+1)*curr_w > best) {
	    best = (i-k+1)*curr_w;
	  }
	}
      }
    }
    printf("%d\n", best);

  }
  return 0;
}
