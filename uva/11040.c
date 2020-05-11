#include <stdio.h>

int wall[9][9];

int main(void)
{
  int N;
  int i, j;
  int c;

  scanf("%d", &N);
  while (N-- > 0) {
    for (i = 0; i < 9; i += 2) {
      for (j = 0; j <= i; j += 2) {
	scanf("%d", &(wall[i][j]));
      }
    }

    for (i = 0; i < 7; i += 2) {
      for (j = 0; j <= i; j += 2) {
	c = (wall[i][j] - wall[i+2][j] - wall[i+2][j+2]) / 2;
	wall[i+1][j] = wall[i+2][j] + c;
	wall[i+1][j+1] = wall[i+2][j+2] + c;
	wall[i+2][j+1] = c;
      }
    }

    for (i = 0; i < 9; i++) {
      for (j = 0; j < i; j++) {
	printf("%d ", wall[i][j]);
      }
      printf("%d\n", wall[i][i]);
    }
  }

  return 0;
}
