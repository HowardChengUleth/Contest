/* @JUDGE_ID: 1102NT 190 C "" */

/*
 * Parameter of circle from 3 points
 *
 * Author: Howard Cheng
 *
 * This routine computes the parameters of a circle (center and radius)
 * from 3 points.  Returns non-zero if successful, zero if the three
 * points are colinear.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

/* how close to call equal */
#define EPSILON 1E-8

typedef struct {
  double x, y;
} Point;

int circle(Point p1, Point p2, Point p3, Point *center, double *r)
{
  double a,b,c,d,e,f,g;

  a = p2.x - p1.x;
  b = p2.y - p1.y;
  c = p3.x - p1.x;
  d = p3.y - p1.y;
  e = a*(p1.x + p2.x) + b*(p1.y + p2.y);
  f = c*(p1.x + p3.x) + d*(p1.y + p3.y);
  g = 2.0*(a*(p3.y - p2.y) - b*(p3.x - p2.x));
  if (fabs(g) < EPSILON) {
    return 0;
  }
  center->x = (d*e - b*f) / g;
  center->y = (a*f - c*e) / g;
  *r = sqrt((p1.x-center->x)*(p1.x-center->x) +
	    (p1.y-center->y)*(p1.y-center->y));
  return 1;
}

char sign1(double x)
{
  return (x < 0) ? '+' : '-';
}

char sign2(double x)
{
  return (x < 0) ? '-' : '+';
}

void print_eqns(Point center, double r)
{
  double c, d, e;

  c = -2*center.x;
  d = -2*center.y;
  e = center.x*center.x + center.y*center.y - r*r;

  printf("(x %c %0.3f)^2 + (y %c %0.3f)^2 = %0.3f^2\n",
	 sign1(center.x), fabs(center.x),
	 sign1(center.y), fabs(center.y),
	 r);
  printf("x^2 + y^2 %c %0.3fx %c %0.3fy %c %0.3f = 0\n",
	 sign2(c), fabs(c), sign2(d), fabs(d), sign2(e), fabs(e));
}

int main(void)
{
  Point a, b, c, center;
  double r;

  while (scanf("%lf %lf %lf %lf %lf %lf", &a.x, &a.y, &b.x, &b.y, &c.x, &c.y)
	 == 6) {
    circle(a, b, c, &center, &r);
    print_eqns(center, r);
    printf("\n");
  }
  return 0;
}

