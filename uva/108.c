/* @JUDGE_ID: 1102NT 108 C "Dynamic programming" */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_N 100

int matrix[MAX_N][MAX_N];
int hsum[MAX_N][MAX_N][MAX_N];
int n;

int max_vsum(int i, int j)
{
  int k;
  int best, best_end;

  best = best_end = 0;

  for (k = 0; k < n; k++) {
    if (best_end + hsum[i][j][k] > 0) {
      best_end += hsum[i][j][k];
    } else {
      best_end = 0;
    }
    if (best_end > best) {
      best = best_end;
    }
  }

  return best;
}

void test_again(int best)
{
  int best2 = matrix[0][0];
  int i, j, k, l, x, y;
  int sum;

  return;

  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      for (k = i; k < n; k++) {
	for(l = j; l < n; l++) {
	  sum = 0;
	  for (x = i; x <= k; x++) {
	    for (y = j; y <= l; y++) {
	      sum += matrix[x][y];
	    }
	  }
	  if (sum > best2) {
	    best2 = sum;
	  }
	}
      }
    }
  }
  if (best == best2) {
    printf("Test passed.\n");
  } else {
    printf("Test failed.  Real best = %d\n", best2);
    printf("matrix = \n");
    for (i = 0; i < n; i++) {
      for (j = 0; j < n; j++) {
	printf("%d ", matrix[i][j]);
      }
      printf("\n");
    }
  }

}

int main(void)
{
  int i, j, k;
  int best;

  scanf("%d", &n);
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      scanf("%d", &(matrix[i][j]));
    }
  }

  /* compute hsum */
  for (i = 0; i < n; i++) {
    for (k = 0; k < n; k++) {
      hsum[i][i][k] = matrix[k][i];
    }
  }

  for (i = 0; i < n; i++) {
    for (j = i+1; j < n; j++) {
      for (k = 0; k < n; k++) {
	hsum[i][j][k] = hsum[i][j-1][k] + matrix[k][j];
      }
    }
  }

  best = matrix[0][0];
  for (i = 0; i < n; i++) {
    for (j = i; j < n; j++) {
      int temp = max_vsum(i, j);
      if (temp > best) {
	best = temp;
      }
    }
  }

  printf("%d\n", best);

  test_again(best);

  return 0;
}
