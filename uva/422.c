#include <stdio.h>
#include <string.h>

int find_at(char grid[102][102], char *word, int r, int c, int dr, int dc)
{
  while (*word) {
    if (grid[r][c] != *word) {
      return 0;
    }
    r += dr;
    c += dc;
    word++;
  }
  return 1;
}

void find(char grid[102][102], char *word, int l)
{
  int dr[8] = { -1, -1, -1,  0, 0,  1, 1, 1};
  int dc[8] = { -1,  0,  1, -1, 1, -1, 0, 1};
  int r, c, i;

  for (r = 1; r <= l; r++) {
    for (c = 1; c <= l; c++) {
      for (i = 0; i < 8; i++) {
	if (find_at(grid, word, r, c, dr[i], dc[i])) {
	  printf("%d,%d ", r, c);
	  printf("%d,%d\n", r + (strlen(word)-1)*dr[i],
		 c + (strlen(word)-1)*dc[i]);
	  return;
	}
      }
    }
  }

  printf("Not found\n");
}

int main(void)
{
  char grid[102][102];
  int l, i, j;
  char word[101];

  scanf("%d\n", &l);
  for (i = 0; i <= l+1; i++) {
    grid[0][i] = grid[l+1][i] = grid[i][0] = grid[i][l+1] = '*';
  }
  for (i = 1; i <= l; i++) {
    for (j = 1; j <= l; j++) {
      scanf("%c\n", &(grid[i][j]));
    }
  }

  while (scanf("%s", word) == 1 && word[0] != '0') {
    find(grid, word, l);
  }
  return 0;
}
