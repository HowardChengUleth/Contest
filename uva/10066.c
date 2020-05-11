#include <stdio.h>

int n1, n2;

int seq1[100], seq2[100];
int table[101][101];

int main(void)
{
  int i, j;
  int num = 1;

  while (scanf("%d %d", &n1, &n2) == 2 && (n1 || n2)) {
    for (i = 0; i < n1; i++) {
      scanf("%d", seq1 + i);
    }
    for (j = 0; j < n2; j++) {
      scanf("%d", seq2 + j);
    }

    for (i = 0; i <= n1; i++) {
      table[i][0] = 0;
    }
    for (j = 0; j <= n2; j++) {
      table[0][j] = 0;
    }
    for (i = 1; i <= n1; i++) {
      for (j = 1; j <= n2; j++) {
	if (seq1[i-1] == seq2[j-1]) {
	  table[i][j] = table[i-1][j-1] + 1;
	} else {
	  table[i][j] = table[i-1][j];
	  if (table[i][j] < table[i][j-1]) {
	    table[i][j] = table[i][j-1];
	  }
	}
      }
    }
    printf("Twin Towers #%d\n", num++);
    printf("Number of Tiles : %d\n\n", table[n1][n2]);
  }
  return 0;
}
