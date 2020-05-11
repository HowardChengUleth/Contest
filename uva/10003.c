#include <stdio.h>

int l, n;
int cuts[52];   /* add 0 and l as the first and last cut */

int read_case(void) {
  int i;

  scanf("%d", &l);
  if (!l) {
    return 0;
  }
  scanf("%d", &n);
  cuts[0] = 0;
  cuts[n+1] = l;
  for (i = 1; i <= n; i++) {
    scanf("%d", cuts + i);
  }
  
  return 1;
}

int best[52][52];

int compute(int start, int end)
{
  int i;
  int temp;

  if (end - start <= 1) {
    return 0;
  } else if (best[start][end] >= 0) {
    return best[start][end];
  }

  for (i = start+1; i < end; i++) {
    temp = cuts[end] - cuts[start] + compute(start, i) + compute(i, end); 
    if (best[start][end] < 0 || temp < best[start][end]) {
      best[start][end] = temp;
    }
  }
  return best[start][end];
}

void solve_case(void)
{
  int i, j;

  for (i = 0; i <= n+1; i++) {
    for (j = 0; j <= n+1; j++) {
      best[i][j] = -1;
    }
  }

  printf("The minimum cutting is %d.\n", compute(0, n+1));
}

int main(void)
{
  while (read_case()) {
    solve_case();
  }
  return 0;
}
