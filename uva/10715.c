/* @JUDGE_ID: 1102NT 10715 C "" */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int n;
double rock[100];
int irock[100];
int isum;

int read_case(void)
{
  int i;
  double sum = 0;
  double mult = 1;

  scanf("%d", &n);
  if (!n) {
    return 0;
  }
  for (i = 0; i < n; i++) {
    scanf("%lf", rock+i);
    sum += rock[i];
  }

  mult = 10000/sum;

  isum = 0;
  for (i = 0; i < n; i++) {
    isum += (irock[i] = (int)floor(rock[i]*mult+0.5));
  }
  return n;
}

void solve_case(void)
{
  char prev[101][10001];
  int i, j;
  int best;
  int printed;

  for (i = 0; i <= n; i++) {
    for (j = 0; j <= isum; j++) {
      prev[i][j] = -1;
    }
  }
  prev[0][0] = 0;

  for (i = 1; i <= n; i++) {
    for (j = 0; j <= isum; j++) {
      if (prev[i-1][j] >= 0) {
	prev[i][j] = 0;
	if (j+irock[i-1] <= isum) {
	  prev[i][j+irock[i-1]] = 1;
	}
      }
    }
  }

  best = -1;
  for (j = 0; j <= isum; j++) {
    if (prev[n][j] < 0) continue;
    if (best == -1 || abs(isum/2 - j) < abs(isum/2 - best)) {
      best = j;
    }
  }
  /*
  printf("best = %d\n", best);
  printf("isum = %d\n", isum);
  */
  printed = 0;
  i = n;
  for (i = n; i >= 0; i--) {
    /*    printf("prev[%d][%d] = %d\n", i, best, prev[i][best]); */
    if (prev[i][best] == 1) {
      if (printed) {
	printf(" ");
      }
      printf("%d", i);
      printed = 1;
      best -= irock[i-1];
    }
  }
  printf("\n");
}

int main(void)
{
  while (read_case()) {
    solve_case();
  }
  return 0;
}
