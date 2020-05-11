/* @JUDGE_ID: 1102NT 10078 C "" */

/*
 * Orientation analysis
 *
 * Author: Howard Cheng
 * Reference:
 *   http://wilma.cs.brown.edu/courses/cs016/packet/node18.html
 *
 * Given three points a, b, c, it returns whether the path from a to b to c
 * is counterclockwise, clockwise, or undefined.
 *
 * Undefined is returned if the 3 points are colinear, and c is between
 * a and b.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* how close to call equal */
#define EPSILON 1E-8

typedef struct {
  double x, y;
} Point;

/* counterclockwise, clockwise, or undefined */
enum {CCW, CW, CNEITHER};

int ccw(Point a, Point b, Point c)
{
  double dx1 = b.x - a.x;
  double dx2 = c.x - b.x;
  double dy1 = b.y - a.y;
  double dy2 = c.y - b.y;
  double t1 = dy2 * dx1;
  double t2 = dy1 * dx2;

  if (fabs(t1 - t2) < EPSILON) {
    if (dx1 * dx2 < 0 || dy1 * dy2 < 0) {
      if (dx1*dx1 + dy1*dy1 >= dx2*dx2 + dy2*dy2 - EPSILON) {
        return CNEITHER;
      } else {
        return CW;
      }
    } else {
      return CCW;
    }
  } else if (t1 > t2) {
    return CCW;
  } else {
    return CW;
  }
}

int main(void)
{
  int n, i, i2, i3;
  int ocw, occw, o;
  Point polygon[50];
  
  while (scanf("%d", &n) == 1 && n) {
    for (i = 0; i < n; i++) {
      scanf("%lf %lf", &(polygon[i].x), &(polygon[i].y));
    }
    
    ocw = occw = 0;
    for (i = 0; i < n; i++) {
      i2 = (i+1) % n;
      i3 = (i+2) % n;
      o = ccw(polygon[i], polygon[i2], polygon[i3]);
      if (o == CW) {
	ocw = 1;
      } else if (o == CCW) {
	occw = 1;
      }
    }

    if (ocw && occw) {
      printf("Yes\n");
    } else {
      printf("No\n");
    }
  }
  
  return 0;
}
