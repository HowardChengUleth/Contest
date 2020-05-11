/* @JUDGE_ID: 1102NT 326 C "" */

#include <stdio.h>

int n, k, table[10][10];

int read_case(void)
{
  int i;

  scanf("%d", &n);
  if (n) {
    for (i = 0; i < n; i++) {
      scanf("%d", &(table[0][i]));
    }
    scanf("%d", &k);
  }
  return n;
}

void build_table(void)
{
  int i, j;

  for (i = 1; i < n; i++) {
    for (j = 0; j < n-i; j++) {
      table[i][j] = table[i-1][j+1] - table[i-1][j];
    }
  }
}

int value(int k)
{
  int vals[10];
  int i;

  for (i = 0; i < n; i++) {
    vals[i] = table[i][n-1-i];
  }
  while (k-- > 0) {
    for (i = n-2; i >= 0; i--) {
      vals[i] += vals[i+1];
    }
  }
  return vals[0];
}

int main(void)
{

  while (n = read_case()) {
    build_table();
    printf("Term %d of the sequence is %d\n", n+k, value(k));
  }
  return 0;
}
