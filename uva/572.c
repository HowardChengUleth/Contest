/* @JUDGE_ID: 1102NT 572 C "" */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int n, m;
int grid[100][100];
int label;
int dir_i[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dir_j[8] = {-1, 0, 1, -1, 1, -1, 0, 1};


void mark_all(int i, int j, int label)
{
  int i2, j2, k;

  for (k = 0; k < 8; k++) {
    i2 = i + dir_i[k];
    j2 = j + dir_j[k];
    if (0 <= i2 && i2 < m && 0 <= j2 && j2 < n && grid[i2][j2] == -1) {
      grid[i2][j2] = label;
      mark_all(i2, j2, label);
    }
  } 
}

int main(void)
{
  char buffer[1000];
  int i, j;

  while (scanf("%d %d", &m, &n) == 2 && m > 0) {
    scanf("\n");
    for (i = 0; i < m; i++) {
      fgets(buffer, 1000, stdin);
      for (j = 0; j < n; j++) {
	if (buffer[j] == '*') {
	  grid[i][j] = 0;
	} else {
	  assert(buffer[j] == '@');
	  grid[i][j] = -1;
	}
      }
    }
    
    label = 0;
    for (i = 0; i < m; i++) {
      for (j = 0; j < n; j++) {
	if (grid[i][j] == -1) {
	  grid[i][j] = ++label;
	  mark_all(i, j, label);
	}
      }
    }
    printf("%d\n", label);
  }
  return 0;
}
