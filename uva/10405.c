/* @JUDGE_ID: 1102NT 10405 C "" */

#include <stdio.h>
#include <string.h>

int max(int a, int b)
{
  return (a > b) ? a : b;
}

int main(void)
{
  char s1[1002], s2[1002];
  int len[1001][1001];
  int i, j;

  for (i = 0; i < 1001; i++) {
    len[i][0] = len[0][i] = 0;
  }

  while (fgets(s1, 1002, stdin)) {
    fgets(s2, 1002, stdin);
    s1[strlen(s1)-1] = 0;
    s2[strlen(s2)-1] = 0;
    for (i = 1; i <= strlen(s1); i++) {
      for (j = 1; j <= strlen(s2); j++) {
	if (s1[i-1] == s2[j-1]) {
	  len[i][j] = 1 + len[i-1][j-1];
	} else {
	  len[i][j] = max(len[i-1][j], len[i][j-1]);
	}
      }
    }
    printf("%d\n", len[strlen(s1)][strlen(s2)]);
  }
  return 0;
}
