#include <stdio.h>
#include <string.h>

int n1, n2;

char seq1[102], seq2[102];
int table[101][101];

int main(void)
{
  int i, j;
  int num = 1;

  while (fgets(seq1, 102, stdin) && seq1[0] != '#') {
    fgets(seq2, 102, stdin);
    n1 = strlen(seq1)-1;
    n2 = strlen(seq2)-1;

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
    printf("Case #%d: ", num++);
    printf("you can visit at most %d cities.\n", table[n1][n2]);
  }
  return 0;
}
