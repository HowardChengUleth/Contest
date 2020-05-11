#include <stdio.h>
#include <ctype.h>

int m, n;
char grid[52][52];

int found(int r, int c, char *word, int dr, int dc)
{
  int i;

  for (i = 0; word[i]; i++) {
    if (toupper(word[i]) != grid[r][c]) {
      return 0;
    }
    r += dr;
    c += dc;
  }
  return 1;
}

void search(char *word)
{
  int i, j;
  int dr, dc;

  for (i = 1; i <= m; i++) {
    for (j = 1; j <= n; j++) {
      for (dr = -1; dr <= 1; dr++) {
	for (dc = -1; dc <= 1; dc++) {
	  if ((dr || dc) && found(i, j, word, dr, dc)) {
	    printf("%d %d\n", i, j);
	    return;
	  }
	}
      }
    }
  }
}

int main(void)
{
  int cases;
  int i, j;
  int k;
  char word[1024];

  scanf("%d", &cases);

  while (cases-- > 0) {
    scanf("%d %d\n", &m, &n);

    for (i = 0; i <= m+1; i++) {
      for (j = 0; j <= n+1; j++) {
	grid[i][j] = '*';
      }
    }

    for (i = 1; i <= m; i++) {
      for (j = 1; j <= n; j++) {
	grid[i][j] = toupper(getchar());
      }
      getchar();
    }

    scanf("%d", &k);
    while (k-- > 0) {
      scanf("%s", word);
      search(word);
    }

    if (cases) {
      printf("\n");
    }
  }

  return 0;
}
