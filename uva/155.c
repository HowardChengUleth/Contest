#include <stdio.h>

typedef struct {
  int x, y;
  int length;
} Square;

Square sq[1000000];
int num_sq;

void draw(int cx, int cy, int k)
{
  sq[num_sq].x = cx-k;
  sq[num_sq].y = cy-k;
  sq[num_sq].length = 2*k+1;
  num_sq++;
  
  if (k == 1) {
    return;
  }

  draw(cx-k, cy-k, k/2);
  draw(cx-k, cy+k, k/2);
  draw(cx+k, cy-k, k/2);
  draw(cx+k, cy+k, k/2);
  
}

int inside(Square sq, int x, int y)
{
  return (sq.x <= x && x < sq.x+sq.length &&
	  sq.y <= y && y < sq.y+sq.length);
}

int main(void)
{
  int k, x, y;
  int count;
  int i;

  while (scanf("%d %d %d", &k, &x, &y) == 3 && (k || x || y)) {
    num_sq = 0;
    draw(1024, 1024, k);
    count = 0;
    for (i = 0; i < num_sq; i++) {
      if (inside(sq[i], x, y)) {
	count++;
      } else {
      }
    }
    printf("%3d\n", count);
  }
  return 0;
}
