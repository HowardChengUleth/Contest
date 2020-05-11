#include <stdio.h>


void do_case(void)
{
  int N, G;
  int P[1000], W[1000], MW[100];
  int best[2][31];
  int curr_row = 0;
  int i, j, k, temp;
  int best_sum = 0;

  scanf("%d", &N);
  for (i = 0; i < N; i++) {
    scanf("%d %d", P+i, W+i);
  }
  scanf("%d", &G);
  for (i = 0; i < G; i++) {
    scanf("%d", MW+i);
  }

  /* initialize first row */
  best[curr_row][0] = 0;
  for (j = 1; j <= 30; j++) {
    best[curr_row][j] = -1;
  }
  curr_row = 1 - curr_row;

  /* consider one item at a time */
  for (k = 0; k < N; k++) {
    for (j = 0; j <= 30; j++) {
      best[curr_row][j] = -1;
    }
    for (j = 0; j <= 30; j++) {
      if (best[1-curr_row][j] < 0) continue;
      
      /* try doing it without adding item k */
      if (best[curr_row][j] < best[1-curr_row][j]) {
	best[curr_row][j] = best[1-curr_row][j];
      }

      /* try doing it by adding item k */
      if (j + W[k] <= 30 && 
	  best[1-curr_row][j] + P[k] > best[curr_row][j + W[k]]) {
	best[curr_row][j+W[k]] = best[1-curr_row][j] + P[k];
      }
    }
    curr_row = 1 - curr_row;
  }

  curr_row = 1 - curr_row;
  for (i = 0; i < G; i++) {
    temp = 0;
    for (j = 0; j <= MW[i]; j++) {
      if (best[curr_row][j] > temp) {
	temp = best[curr_row][j];
      }
    }
    best_sum += temp;
  }
  
  printf("%d\n", best_sum);
}


int main(void)
{
  int T;
  
  scanf("%d", &T);
  while (T-- > 0) {
    do_case();
  }
  return 0;
}
