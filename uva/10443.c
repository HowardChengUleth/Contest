#include <stdio.h>

int beat(char a, char b)
{
  return (a == 'R' && b == 'S') ||
    (a == 'S' && b == 'P') ||
    (a == 'P' && b == 'R');
}

void process(char grid[100][101], int r, int c)
{
  char temp_grid[100][101];
  int i, j;

  for (i = 0; i < r; i++) {
    for (j = 0; j < c; j++) {
      temp_grid[i][j] = grid[i][j];
    }
  }

  for (i = 0; i < r; i++) {
    for (j = 0; j < c; j++) {
      if (i > 0 && beat(temp_grid[i-1][j], temp_grid[i][j])) {
	grid[i][j] = temp_grid[i-1][j];
      }
      if (i < r-1 && beat(temp_grid[i+1][j], temp_grid[i][j])) {
	grid[i][j] = temp_grid[i+1][j];
      }
      if (j > 0 && beat(temp_grid[i][j-1], temp_grid[i][j])) {
	grid[i][j] = temp_grid[i][j-1];
      }
      if (j < c-1 && beat(temp_grid[i][j+1], temp_grid[i][j])) {
	grid[i][j] = temp_grid[i][j+1];
      }
    }
  }
}

int main(void)
{
  int t;
  int r, c, n;
  char grid[100][101];
  int i;

  scanf("%d", &t);
  while (t-- > 0) {
    scanf("%d %d %d", &r, &c, &n);
    for (i = 0; i < r; i++) {
      scanf("%s", grid[i]);
    }

    while (n-- > 0) {
      process(grid, r, c);
    }

    for (i = 0; i < r; i++) {
      printf("%s\n", grid[i]);
    }

    if (t) {
      printf("\n");
    }
  }
  
  return 0;
}
