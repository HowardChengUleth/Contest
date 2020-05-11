#include <stdio.h>

char win[1000001];   /* 1 = first player wins, 0 = loses */


int main(void)
{
  int set[10];
  int m, n, i, j;

  while (scanf("%d", &n) == 1) {
    scanf("%d", &m);
    for (i = 0; i < m; i++) {
      scanf("%d", set+i);
    }
    win[1] = 1;
    for (i = 2; i <= n; i++) {
      win[i] = !win[i-1];
      for (j = 0; j < m && !win[i]; j++) {
	if (i == set[j] || (i-set[j] >= 0 && !win[i-set[j]])) {
	  win[i] = 1;
	}
      }
    }
    printf("%s wins\n", (win[n] ? "Stan" : "Ollie"));
  }
  return 0;
}
