/* @JUDGE_ID: 1102NT 191 C "" */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

typedef struct {
  int x, y;
} Point;


int direction(Point p1, Point p2, Point p3)
{
  int x1 = p3.x - p1.x;
  int y1 = p3.y - p1.y;
  int x2 = p2.x - p1.x;
  int y2 = p2.y - p1.y;
  return x1*y2 - x2*y1;
}

int on_segment(Point p1, Point p2, Point p3)
{
  return ((p1.x <= p3.x && p3.x <= p2.x) || (p2.x <= p3.x && p3.x <= p1.x)) &&
    ((p1.y <= p3.y && p3.y <= p2.y) || (p2.y <= p3.y && p3.y <= p1.y));
}

int intersect(Point a1, Point a2, Point b1, Point b2)
{
  int d1 = direction(b1, b2, a1);
  int d2 = direction(b1, b2, a2);
  int d3 = direction(a1, a2, b1);
  int d4 = direction(a1, a2, b2);

  if (((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) &&
      ((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0))) {
    return 1;
  } else {
    return (d1 == 0 && on_segment(b1, b2, a1)) ||
      (d2 == 0 && on_segment(b1, b2, a2)) ||
      (d3 == 0 && on_segment(a1, a2, b1)) ||
      (d4 == 0 && on_segment(a1, a2, b2));
  }
}

int main(void)
{
  Point a, b, c, d, l1, l2;
  int xl, yt, xr, yb, t;
  int cases;

  scanf("%d", &cases);
  while (cases-- > 0) {
    scanf("%d %d %d %d %d %d %d %d",
	  &l1.x, &l1.y, &l2.x, &l2.y, &xl, &yt, &xr, &yb);
    if (xl > xr) {
      t = xl;
      xl = xr;
      xr = t;
    }
    if (yb > yt) {
      t = yb;
      yb = yt;
      yt = t;
    }
    a.x = xl; a.y = yt;
    b.x = xr; b.y = yt;
    c.x = xr; c.y = yb;
    d.x = xl; d.y = yb;

    if ((xl <= l1.x && l1.x <= xr && yb <= l1.y && l1.y <= yt) ||
	(xl <= l2.x && l2.x <= xr && yb <= l2.y && l2.y <= yt) ||
	intersect(a, b, l1, l2) || intersect(b, c, l1, l2) ||
	intersect(c, d, l1, l2) || intersect(d, a, l1, l2)) {
      printf("T\n");
    } else {
      printf("F\n");
    }
  }
  return 0;
}
