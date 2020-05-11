/* @JUDGE_ID: 1102NT 438 C "" */

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

int main(void)
{
    Point p1, p2, p3, center;
    double r, pi;

    pi = atan(1)*4;
    while (scanf("%lf %lf %lf %lf %lf %lf", &p1.x, &p1.y, &p2.x, &p2.y,
		 &p3.x, &p3.y) == 6) {
	circle(p1, p2, p3, &center, &r);
	printf("%0.2f\n", 2*r*pi);
    }
    return 0;
}
