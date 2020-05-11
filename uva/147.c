/* @JUDGE_ID: 1102NT 147 C "Dynamic programming */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int denom[] = {5, 10, 20, 50, 100, 200, 500, 1000, 2000, 5000, 10000};
int num = 11;

/* number of ways to form i using coins 0..j */
unsigned long long ways[6001][11];   

void comp_ways(void) 
{
  int i, j;

  for (j = 0; j < num; j++) {
    ways[0][j] = 1;
  }
  
  for (i = 1; i <= 6000; i++) {
    for (j = 0; j < num; j++) {
      ways[i][j] = (j) ? ways[i][j-1] : 0;
      if (denom[j] <= i) { 
	ways[i][j] += ways[i - denom[j]][j];
      }		   
    }
  }
}

int main(void)
{
  double t;
  int n, i;

  for (i = 0; i < num; i++) {
    denom[i] /= 5;
  }
  comp_ways();

  while (scanf("%lf", &t) == 1 && t != 0.0) {
    n = (int)(t * 100.0 + 0.5) / 5;
    printf("%6.2f%17llu\n", t, ways[n][num-1]);
  }

  return 0;
}
