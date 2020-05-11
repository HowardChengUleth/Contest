#include <stdio.h>
#include <string.h>

/* 0 = no change, -1 = strip first, 1 = strip last */
int best_move[1001][1001];   
int best[1001][1001];   /* -1 = uninitialized */

int compute(char *str, int s, int e)
{
  int t;

  if (best[s][e] >= 0) {
    return best[s][e];
  }
  if (s >= e) {
    best[s][e] = 0;
    best_move[s][e] = 0;
  } else if (str[s] == str[e]) {
    best[s][e] = compute(str, s+1, e-1);
    best_move[s][e] = 0;
  } else {
    best[s][e] = compute(str, s+1, e) + 1;
    best_move[s][e] = -1;
    if ((t = compute(str, s, e-1) + 1) < best[s][e]) {
      best[s][e] = t;
      best_move[s][e] = 1;
    }
  }
  return best[s][e];
}

void print(char *str, int s, int e)
{
  if (s > e) {
    return;
  }
  if (s == e) {
    putchar(str[s]);
  } else if (best_move[s][e] == 0) {
    putchar(str[s]);
    print(str, s+1, e-1);
    putchar(str[e]);
  } else if (best_move[s][e] < 0) {
    putchar(str[s]);
    print(str, s+1, e);
    putchar(str[s]);
  } else {
    putchar(str[e]);
    print(str, s, e-1);
    putchar(str[e]);
  }
}

int main(void)
{
  char str[1001];
  int i, j, n;
  int to_add;

  while (scanf("%s", str) == 1) {
    n = strlen(str);
    for (i = 0; i <= n; i++) {
      for (j = 0; j <= n; j++) {
	best[i][j] = -1;
      }
    }
    to_add = compute(str, 0, n-1);
    printf("%d ", to_add);
    print(str, 0, n-1);
    printf("\n");
  }
  return 0;
}
