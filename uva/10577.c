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
  Point a, b, c, center;
  double r, theta;
  double x, y;
  int n, i;
  double xmin, xmax, ymin, ymax;
  double pi = atan(1)*4;
  int case_no = 1;

  while (scanf("%d", &n) == 1 && n > 0) {
    scanf("%lf %lf %lf %lf %lf %lf", &a.x, &a.y, &b.x, &b.y, &c.x, &c.y);
    circle(a, b, c, &center, &r);
    theta = atan2(a.y-center.y, a.x-center.x);
    
    xmin = xmax = a.x;
    ymin = ymax = a.y;

    for (i = 0; i < n; i++) {
      theta += 2*pi/n;
      x = center.x + r*cos(theta);
      y = center.y + r*sin(theta);
      if (x > xmax) xmax = x;
      if (x < xmin) xmin = x;
      if (y > ymax) ymax = y;
      if (y < ymin) ymin = y;
    }

    printf("Polygon %d: %.3f\n", case_no++, (xmax-xmin)*(ymax-ymin));

  }
  return 0;
}
