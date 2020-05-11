#include <stdio.h>

int H, W;
int board[501][501];

void clear(void)
{
  int y, x;

  for (y = 1; y <= H; y++) {
    for (x = 1; x <= W; x++) {
      board[y][x] = 0;
    }
  }
}

int mark(int x1, int y1, int x2, int y2)
{
  int minx = (x1 < x2) ? x1 : x2,
    miny = (y1 < y2) ? y1 : y2;
  int maxx = x1+x2 - minx, 
    maxy = y1+y2-miny;
  int y, x;
  int count = 0;

  for (x = minx; x <= maxx; x++) {
    for (y = miny; y <= maxy; y++) {
      if (board[y][x]) continue;
      board[y][x] = 1;
      count++;
    }
  }
  return count;

}
  

int main(void)
{
  int N, x1, y1, x2, y2;
  int empty;

  while (scanf("%d %d %d", &W, &H, &N) == 3 && (W || H || N)) {
    clear();
    empty = W*H;
    while (N-- > 0) {
      scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
      empty -= mark(x1, y1, x2, y2);
    }
    if (!empty) {
      printf("There is no empty spots.\n");
    } else if (empty == 1) {
      printf("There is one empty spot.\n");
    } else {
      printf("There are %d empty spots.\n", empty);
    }
  }
  return 0;
}
