/* @JUDGE_ID: 1102NT 741 C "" */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 301

char P[MAX_LEN][MAX_LEN];
int t;

void fill_column(int c)
{
  char temp[MAX_LEN][MAX_LEN];
  int i, j;

  j = 0;
  for (i = 1; i <= t; i++) {
    temp[i-1][j] = P[i][t];
  }
  j++;

  while (j < c) {
    for (i = 1; i <= t; i++) {
      temp[i-1][j] = P[i][j];
    }
    j++;
  }
  for (i = 1; i <= t; i++) {
    temp[i-1][j] = 0;
  }


  qsort(temp, t, sizeof(char[MAX_LEN]), strcmp);

  for (i = 1; i <= t; i++) {
    P[i][c] = temp[i-1][j-1];
  }
}

int main(void)
{
  char str[MAX_LEN];
  int index;
  int first = 1;
  int i;

  while (scanf("%s %d", str, &index) == 2 && 
	 (strcmp(str, "END") || index > 0)) {
    if (first) {
      first = 0;
    } else {
      printf("\n");
    }

    t = strlen(str);
    for (i = 1; i <= t; i++) {
      P[i][t] = str[i-1];
    }

    for (i = 1; i < t; i++) {
      fill_column(i);
    }

    for (i = 1; i <= t; i++) {
      putchar(P[index][i]);
    }
    printf("\n");
  }
  return 0;
}
