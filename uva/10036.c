/* @JUDGE_ID: 1102NT 10036 C "" */

#include <stdio.h>

void solve(int n, int k, int *seq)
{
  char table[2][100];
  int row, nextrow, i, j, val;

  row = 0;
  for (i = 0; i < k; i++) {
    table[row][i] = 0;
  }
  val = seq[0] % k;
  if (val < 0) val += k;
  table[row][val] = 1;
  
  for (i = 1; i < n; i++) {
    nextrow = 1 - row;
    for (j = 0; j < k; j++) {
      table[nextrow][j] = 0;
    }
    for (j = 0; j < k; j++) {
      if (table[row][j]) {
	val = (j + seq[i]) % k;
	if (val < 0) val += k;
	table[nextrow][val] = 1;
	val = (j - seq[i]) % k;
	if (val < 0) val += k;
	table[nextrow][val] = 1;
      }
    }
    row = nextrow;
  }

  if (table[row][0]) {
    printf("Divisible\n");
  } else {
    printf("Not divisible\n");
  }
}

int main(void)
{
  int m, n, k, seq[10000], i;

  scanf("%d", &m);
  while (m-- > 0) {
    scanf("%d %d", &n, &k);
    for (i = 0; i < n; i++) {
      scanf("%d", seq+i);
    }
    solve(n, k, seq);
  }
  return 0;
}
