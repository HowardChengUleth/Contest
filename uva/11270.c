#include <stdio.h>

#define MAX_N 100

char board[MAX_N][MAX_N];
int m, n;
unsigned long long myans[MAX_N][MAX_N];

unsigned long long count(char board[][MAX_N], int r, int c)
{
  unsigned long long ways = 0;

  if (r >= m) {
    return 1;
  } else if (c >= n) {
    return count(board, r+1, 0);
  } else if (board[r][c]) {
    return count(board, r, c+1);
  }

  /* try putting horizontally */
  if (c+1 < n && !board[r][c+1]) {
    board[r][c] = board[r][c+1] = 1;
    ways += count(board, r, c+1);
    board[r][c] = board[r][c+1] = 0;
  }

  /* try putting vertically */
  if (r+1 < m && !board[r+1][c]) {
    board[r][c] = board[r+1][c] = 1;
    ways += count(board, r, c+1);
    board[r][c] = board[r+1][c] = 0;
  }
  return ways;
}

int main(void)
{
  int i, j, k;
  unsigned long long ans;

  for (m = 1; m <= MAX_N; m++) {
    for (n = 1; n <= MAX_N; n++) {
      if (m * n <= 100 && m <= n) {
	for (i = 0; i < m; i++) {
	  for (j = 0; j < n; j++) {
	    board[i][j] = 0;
	  }
	}
	if (m * n % 2 != 0) {
	  ans = 0;
	} else if (m == 1) {
	  ans = 1;
	} else if (m == 2) {
	  ans[m][0
	  prev2 = 0;
	  for (k = 1; k <= n; k++) {
	    ans = prev1 + prev2;
	    prev2 = prev1;
	    prev1 = ans;
	  }
	} else {
	  ans = count(board, 0, 0);
	}
	printf("ans[%d][%d] = %lluLLU;\n", m, n, ans);
	printf("ans[%d][%d] = %lluLLU;\n", n, m, ans);
	fflush(stdout);
      }
    }
  }

  return 0;
}
