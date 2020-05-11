#include <stdio.h>

char grid[100][101];
int n, m;

/* block[i][j][k] = whether column k is completely 1's from row i to row j */
char block[100][100][100]; 

int main(void)
{
  int i, j, k;
  int count;
  int lcount;

  while (scanf("%d", &n) == 1 && n) {
    scanf("%d", &m);

    for (i = 0; i < n; i++) {
      scanf("%s", grid[i]);
    }

    for (i = 0; i < n; i++) {
      for (k = 0; k < m; k++) {
	block[i][i][k] = (grid[i][k] == '1');
      }
      for (j = i+1; j < n; j++) {
	for (k = 0; k < m; k++) {
	  block[i][j][k] = block[i][j-1][k] && (grid[j][k] == '1');
	}
      }
    }

    count = 0;
    for (i = 0; i < n; i++) {
      for (j = i; j < n; j++) {
	k = 0;
	while (k < m) {
	  lcount = 0;
	  while (k < m && block[i][j][k++]) {
	    lcount++;
	  }
	  count += (lcount)*(lcount+1)/2;
	}
      }
    }
    printf("%d\n", count);
  }
  return 0;
}
