/* @JUDGE_ID: 1102NT 847 C "" */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* indexed by powers of 2, 3, 5, 7 */
int table[33][22][15][13];

void filltable(int n, long long p, int e1, int e2, int e3, int e4)
{
  int a1, a2, a3, a4;
  if (table[e1][e2][e3][e4]) {
    return;
  }

  if (p*9 >= n) {
    table[e1][e2][e3][e4] = 1;
    return;
  }

  a1 = e1+1; a2 = e2; a3 = e3; a4 = e4;
  filltable(n, p*2, a1, a2, a3, a4);
  if (-table[a1][a2][a3][a4] > table[e1][e2][e3][e4]) {
    table[e1][e2][e3][e4] = -table[a1][a2][a3][a4];
    return;
  }
  a1 = e1; a2 = e2+1; a3 = e3; a4 = e4;
  filltable(n, p*3, a1, a2, a3, a4);
  if (-table[a1][a2][a3][a4] > table[e1][e2][e3][e4]) {
    table[e1][e2][e3][e4] = -table[a1][a2][a3][a4];
    return;
  }
  a1 = e1+2; a2 = e2; a3 = e3; a4 = e4;
  filltable(n, p*4, a1, a2, a3, a4);
  if (-table[a1][a2][a3][a4] > table[e1][e2][e3][e4]) {
    table[e1][e2][e3][e4] = -table[a1][a2][a3][a4];
    return;
  }
  a1 = e1; a2 = e2; a3 = e3+1; a4 = e4;
  filltable(n, p*5, a1, a2, a3, a4);
  if (-table[a1][a2][a3][a4] > table[e1][e2][e3][e4]) {
    table[e1][e2][e3][e4] = -table[a1][a2][a3][a4];
    return;
  }
  a1 = e1+1; a2 = e2+1; a3 = e3; a4 = e4;
  filltable(n, p*6, a1, a2, a3, a4);
  if (-table[a1][a2][a3][a4] > table[e1][e2][e3][e4]) {
    table[e1][e2][e3][e4] = -table[a1][a2][a3][a4];
    return;
  }
  a1 = e1; a2 = e2; a3 = e3; a4 = e4+1;
  filltable(n, p*7, a1, a2, a3, a4);
  if (-table[a1][a2][a3][a4] > table[e1][e2][e3][e4]) {
    table[e1][e2][e3][e4] = -table[a1][a2][a3][a4];
    return;
  }
  a1 = e1+3; a2 = e2; a3 = e3; a4 = e4;
  filltable(n, p*8, a1, a2, a3, a4);
  if (-table[a1][a2][a3][a4] > table[e1][e2][e3][e4]) {
    table[e1][e2][e3][e4] = -table[a1][a2][a3][a4];
    return;
  }
  a1 = e1; a2 = e2+2; a3 = e3; a4 = e4;
  filltable(n, p*9, a1, a2, a3, a4);
  if (-table[a1][a2][a3][a4] > table[e1][e2][e3][e4]) {
    table[e1][e2][e3][e4] = -table[a1][a2][a3][a4];
    return;
  }
  table[e1][e2][e3][e4] = -1;
}

int main(void)
{
  int n, i, j, k, l;
  
  while (scanf("%d", &n) == 1) {
    /* clear table */
    for (i = 0; i < 33; i++)
      for (j = 0; j < 22; j++)
	for (k = 0; k < 15; k++)
	  for (l = 0; l < 13; l++)
	    table[i][j][k][l] = 0;

    filltable(n, 1, 0, 0, 0, 0);
    if (table[0][0][0][0] == 1) {
      printf("Stan wins.\n");
    } else {
      printf("Ollie wins.\n");
    }
  }
  return 0;
}
