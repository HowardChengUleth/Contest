#include <stdio.h>

char grid[25][26];
int n;

void mark(int i, int j)
{
  int di, dj;

  grid[i][j] = '2';

  for (di = -1; di <= 1; di++) {
    for (dj = -1; dj <= 1; dj++) {
      if (0 <= i + di && i + di < n &&
	  0 <= j + dj && j + dj < n &&
	  grid[i+di][j+dj] == '1') {
	mark(i+di, j+dj);
      }
    }
  }
}

int count(void)
{
  int c = 0;
  int i, j;

  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      if (grid[i][j] == '1') {
	c++;
	mark(i, j);
      }
    }
  }

  return c;
}

int main(void)
{
  int i;
  int num = 1;

  while (scanf("%d", &n) == 1) {
    for (i = 0; i < n; i++) {
      scanf("%s", grid[i]);
    }

    printf("Image number %d contains %d war eagles.\n", num++,
	   count());
  }
  return 0;
}
