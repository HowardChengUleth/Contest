#include <stdio.h>


int main(void)
{
  int r, c, r2, c2;
  int i, j, k;
  int star;
  char is_star;
  char grid[100][101];
  int dr[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
  int dc[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

  while (scanf("%d %d", &r, &c) == 2 && r && c) {
    for (i = 0; i < r; i++) {
      scanf("%s", grid[i]);
    }

    star = 0;
    for (i = 0; i < r; i++) {
      for (j = 0; j < c; j++) {
	if (grid[i][j] == '*') {
	  is_star = 1;
	  for (k = 0; k < 8 && is_star; k++) {
	    r2 = i + dr[k];
	    c2 = j + dc[k];
	    if (0 <= r2 && r2 < r && 0 <= c2 && c2 < c &&
		grid[r2][c2] == '*') {
	      is_star = 0;
	    }
	  }
	  star += is_star;
	}
      }
    }
    printf("%d\n", star);
  }
  return 0;
}
