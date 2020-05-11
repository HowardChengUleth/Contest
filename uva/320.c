/* @JUDGE_ID: 1102NT 320 C "" */

#include <stdio.h>
#include <assert.h>

char bitmap[32][32];

void print(void)
{
  int x, y;

  for (y = 31; y >= 0; y--) {
    for (x = 0; x < 32; x++) {
      putchar(bitmap[x][y]);
    }
    printf("\n");
  }
}

void trace(int x, int y)
{
  int i, j;
  char c;

  for (i = 0; i < 32; i++) {
    for (j = 0; j < 32; j++) {
      bitmap[i][j] = '.';
    }
  }

  while ((c = getchar()) != '.') {
    switch (c) {
    case 'N':
      bitmap[x][y++] = 'X';
      break;
    case 'S':
      bitmap[x-1][--y] = 'X';
      break;
    case 'E':
      bitmap[x++][y-1] = 'X';
      break;
    case 'W':
      bitmap[--x][y] = 'X';
      break;
    default:
      assert(0);
    }
  }
}

int main(void)
{
  int cases;
  int x, y, i;
  
  scanf("%d", &cases);
  for (i = 1; i <= cases; i++) {
    printf("Bitmap #%d\n", i);

    scanf("%d %d\n", &x, &y);
    trace(x, y);
    print();
    printf("\n");
  }

  return 0;
}
