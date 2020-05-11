/* @JUDGE_ID: 1102NT 348 C "Dynamic programming" */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>

#define MAX_N 10

int d[MAX_N+1];
int M[MAX_N+1][MAX_N+1];
int factor[MAX_N+1][MAX_N+1];
int n;

int read_case(void)
{
  int t1, t2, i, c;

  scanf("%d", &n);
  if (!n) {
    return 0;
  }

  c = 0;
  for (i = 0; i < n; i++) {
    scanf("%d %d", &t1, &t2);
    if (!i) {
      d[c++] = t1;
    } else {
      assert(d[c-1] == t1);
    }
    d[c++] = t2;
  }

  return 1;
}

void dp(void)
{
  int i, j, k, diag, best_k, t;

  for (i = 1; i <= n; i++) {
    M[i][i] = 0;
  }
  for (diag = 1; diag <= n-1; diag++) {
    for (i = 1; i <= n - diag; i++) {
      j = i + diag;
      for (k = i; k <= j-1; k++) {
	t = M[i][k] + M[k+1][j] + d[i-1]*d[k]*d[j];
	if (k == i || t < M[i][j]) {
	  best_k = k;
	  M[i][j] = t;
	}
      }
      factor[i][j] = best_k;
    }
  }
}

void print_mult(int i, int j)
{
  int k;

  if (i == j) {
    printf("A%d", i);
  } else {
    k = factor[i][j];
    printf("(");
    print_mult(i, k);
    printf(" x ");
    print_mult(k+1, j);
    printf(")");
  }
}

int main(void)
{
  int case_no = 0;

  while (read_case()) {
    dp();
    printf("Case %d: ", ++case_no);
    print_mult(1, n);
    printf("\n");
  }
  return 0;
}
