/* @JUDGE_ID: 1102NT 104 C "" */

#include <stdio.h>
#include <assert.h>

double rate[20][20][20];
int prev[20][20][20];

int found(int n, int e)
{
  int i;
  for (i = 0; i < n; i++) {
    if (rate[e][i][i] > 1.01) {
      return i;
    }
  }
  return -1;
}

void print_soln(int s, int t, int e)
{
  if (e == 0) {
    printf("%d %d", s+1, t+1);
  } else {
    print_soln(s, prev[e][s][t], e-1);
    printf(" %d", t+1);
  }
}

int main(void)
{
  int n, i, j, k, exchanges, t;
  double temp;
  
  while (scanf("%d", &n) == 1) {
    for (i = 0; i < n; i++) {
      for (j = 0; j < n; j++) {
	if (i == j) {
	  rate[0][i][j] = 1.0;
	} else {
	  scanf("%lf", &(rate[0][i][j]));
	}
      }
    }
#ifdef DEBUG
    for (i  = 0; i < n; i++) {
      for (j = 0; j < n; j++) {
	printf("%5.3f ", rate[0][i][j]);
      }
      printf("\n");
    }
    printf("\n");
#endif
    for (exchanges = 1; exchanges < n; exchanges++) {
#ifdef DEBUG
  printf("exchanges = %d:\n\n", exchanges);
#endif
      for (i = 0; i < n; i++) {
	for (j = 0; j < n; j++) {
	  rate[exchanges][i][j] = rate[exchanges-1][i][0]*rate[0][0][j];
	  prev[exchanges][i][j] = 0;
	  for (k = 1; k < n; k++) {
	    temp = rate[exchanges-1][i][k]*rate[0][k][j];
	    if (temp > rate[exchanges][i][j]) {
	      rate[exchanges][i][j] = temp;
	      prev[exchanges][i][j] = k;
	    }
	  }
#ifdef DEBUG
	  printf("(%5.3f,%d) ", rate[exchanges][i][j], prev[exchanges][i][j]);
#endif
	}
#ifdef DEBUG
	printf("\n");
#endif
      }
      if (found(n, exchanges) >= 0) {
	break;
      }
    }

    if (exchanges < n) {
      t = found(n, exchanges);
      assert(t >= 0);
      print_soln(t, t, exchanges);
      printf("\n");
    } else {
      printf("no arbitrage sequence exists\n");
    }
  }
  return 0;
}
