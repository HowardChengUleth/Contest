#include <stdio.h>

int days[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int leap(long long y)
{
  return (y % 400 == 0 || (y % 100 != 0 && y % 4 == 0));
}

int valid(int c, int y, int m, int d)
{
  long long yy = c*100+y;

  days[2] = (leap(yy)) ? 29 : 28;

  return (1 <= m && m <= 12 && 1 <= d && d <= days[m]);
}

int better(int x, int y, int z, int xx, int yy, int zz)
{
  return (xx == -1 || 
	  (x < xx || (x == xx && y < yy) || (x == xx && y == yy && z < zz)));
}

int main(void)
{
  int c, x, y, z;
  int by, bm, bd;
  int n;

  scanf("%d", &n);
  while (n-- > 0) {
    scanf("%d %d %d %d", &c, &x, &y, &z);
    by = bm = bd = -1;
    if (valid(c, x, y, z) && better(x, y, z, by, bm, bd)) {
      by = x;
      bm = y;
      bd = z;
    }
    if (valid(c, x, z, y) && better(x, z, y, by, bm, bd)) {
      by = x;
      bm = z;
      bd = y;
    }
    if (valid(c, y, x, z) && better(y, x, z, by, bm, bd)) {
      by = y;
      bm = x;
      bd = z;
    }
    if (valid(c, y, z, x) && better(y, z, x, by, bm, bd)) {
      by = y;
      bm = z;
      bd = x;
    }
    if (valid(c, z, x, y) && better(z, x, y, by, bm, bd)) {
      by = z;
      bm = x;
      bd = y;
    }
    if (valid(c, z, y, x) && better(z, y, x, by, bm, bd)) {
      by = z;
      bm = y;
      bd = x;
    }

    if (by >= 0) {
      printf("%02d %02d %02d\n", by, bm, bd);
    } else {
      printf("-1\n");
    } 
  }
  return 0;
}
