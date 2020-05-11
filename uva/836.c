/* @JUDGE_ID: 1102NT 836 C "" */

#include <stdio.h>
#include <string.h>

int main(void)
{
  int cases;
  char A[25][26];
  char column[25][25][25];
  int n, i, j, k;
  int area, temp;

  scanf("%d\n", &cases);

  while (cases-- > 0) {
    scanf("%s", A[0]);
    n = strlen(A[0]);
    for (i = 1; i < n; i++) {
      scanf("%s", A[i]);
    }

    /* compress each column */
    for (k = 0; k < n; k++) {
      for (i = 0; i < n; i++) {
	column[k][i][i] = A[i][k] == '1';
	for (j = i+1; j < n; j++) {
	  column[k][i][j] = column[k][i][j-1] && A[j][k] == '1';
	}
      }
    }

    /* scan through each column */
    area = 0;
    for (i = 0; i < n; i++) {
      for (j = i; j < n; j++) {
	temp = 0;
	for (k = 0; k < n; k++) {
	  if (column[k][i][j]) {
	    temp += j-i+1;
	  } else {
	    temp = 0;
	  }
	  if (temp > area) {
	    area = temp;
	  }
	}
      }
    }
    
    printf("%d\n", area);
    if (cases) {
      printf("\n");
    }
  }

  return 0;
}
