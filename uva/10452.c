#include <stdio.h>

int row[256], col[256];
char *str = "@IEHOVA#";

int main(void)
{
  int m, n;
  int cases;
  int i, j;
  char line[10];

  scanf("%d", &cases);
  while (cases-- > 0) {
    scanf("%d %d", &m, &n);
    for (i = 0; i < m; i++) {
      scanf("%s", line);
      for (j = 0; j < n; j++) {
	row[line[j]] = i;
	col[line[j]] = j;
      }
    }
    
    for (i = 1; str[i]; i++) {
      if (i > 1) {
	printf(" ");
      }
      if (row[str[i-1]] == row[str[i]]) {
	if (col[str[i-1]]-1 == col[str[i]]) {
	  printf("left");
	} else {
	  printf("right");
	}
      } else {
	printf("forth");
      }
    }
    printf("\n");
  }

  return 0;
}
