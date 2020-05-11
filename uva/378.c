/* @JUDGE_ID: 1102NT 378 C "" */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

/* how close to call equal */
#define EPSILON 1E-8

typedef struct {
  double x, y;
} Point;

/* returns 1 if intersect at a point, 0 if not, -1 if the lines coincide */
int intersect_iline(Point a, Point b, Point c, Point d, Point *p)
{
  double r;
  double denom, num1, num2;

  assert((a.x != b.x || a.y != b.y) && (c.x != d.x || c.y != d.y));

  num1 = (a.y - c.y)*(d.x - c.x) - (a.x - c.x)*(d.y - c.y);
  num2 = (a.y - c.y)*(b.x - a.x) - (a.x - c.x)*(b.y - a.y);
  denom = (b.x - a.x)*(d.y - c.y) - (b.y - a.y)*(d.x - c.x);
  
  if (fabs(denom) >= EPSILON) {
    r = num1 / denom;
    p->x = a.x + r*(b.x - a.x);
    p->y = a.y + r*(b.y - a.y);
    return 1;
  } else {
    if (fabs(num1) >= EPSILON) {
      return 0;
    } else {
      return -1;
    }
  }
}

int main(void)
{
  Point a, b, c, d, p;
  int res, n, i;

  scanf("%d", &n);
  printf("INTERSECTING LINES OUTPUT\n");
  for (i = 0; i < n; i++) {
    scanf("%lf %lf %lf %lf %lf %lf %lf %lf", 
	  &a.x, &a.y, &b.x, &b.y, &c.x, &c.y, &d.x, &d.y);
    res = intersect_iline(a, b, c, d, &p);
    if (res == 1) {
      printf("POINT %0.2f %0.2f\n", p.x, p.y);
    } else if (res == 0) {
      printf("NONE\n");
    } else {
      printf("LINE\n");
    }
  }
  printf("END OF OUTPUT\n");
  return 0;
}
