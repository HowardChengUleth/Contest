/* @JUDGE_ID: 1102NT 10189 C "" */

#include <stdio.h>
#include <stdlib.h>

char field[200][201];
int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

int main(void)
{
  int n, m, c, f;
  int i, j, k, i2, j2;

  f = 1;
  while (scanf("%d %d", &n, &m) == 2 && (n > 0 || m > 0)) {
    if (f > 1) {
      printf("\n");
    }
    printf("Field #%d:\n", f++);
    for (i = 0; i < n; i++) {
      scanf("%s", field[i]);
    }
    for (i = 0; i < n; i++) {
      for (j = 0; j < m; j++) {
	if (field[i][j] == '*') {
	  putchar('*');
	} else {
	  c = 0;
	  for (k = 0; k < 8; k++) {
	    i2 = i+dx[k]; j2 = j+dy[k];
	    if (0 <= i2 && i2 < n && 0 <= j2 && j2 < m &&
		field[i2][j2] == '*') {
	      c++;
	    }
	  }
	  putchar(c+'0');
	}
      }
      putchar('\n');
    }
  }
  return 0;
}
