/* @JUDGE_ID: 1102NT 10652 C "" */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>


#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <cassert>

using namespace std;

/* how close to call equal */
const double EPSILON = 1E-8;

struct Point {
  double x, y;
  
  bool operator<(const Point &p) const {
    return y < p.y || (y == p.y && x < p.x);
  }
      
};

/* counterclockwise, clockwise, or undefined */
enum Orientation {CCW, CW, CNEITHER};

/* Global point for computing convex hull */
Point start_p, max_p; 

bool colinear(Point a, Point b, Point c)
{
  double dx1 = b.x - a.x;
  double dx2 = c.x - b.x;
  double dy1 = b.y - a.y;
  double dy2 = c.y - b.y;
  double t1 = dy2 * dx1;
  double t2 = dy1 * dx2;
  return fabs(t1 - t2) < EPSILON;
}

Orientation ccw(Point a, Point b, Point c)
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

bool ccw_cmp(const Point &a, const Point &b)
{
  return ccw(start_p, a, b) == CCW;
}

bool sort_cmp(const Point &a, const Point &b)
{
  if (colinear(start_p, a, max_p) && colinear(start_p, b, max_p)) {
    double dx1 = abs(start_p.x - a.x);
    double dx2 = abs(start_p.x - b.x);
    double dy1 = abs(start_p.y - a.y);
    double dy2 = abs(start_p.y - b.y);
    return dx1 > dx2 || (dx1 == dx2 && dy1 > dy2);
  } else {
    return ccw(start_p, a, b) == CCW;
  }
}

int convex_hull(Point polygon[], int n, Point hull[]) {
  int count, best_i, i;

  sort(polygon, polygon+n);
  for (int i = n-1; i >= 1; i--) {
    if (fabs(polygon[i].x - polygon[i-1].x) < EPSILON &&
	fabs(polygon[i].y - polygon[i-1].y) < EPSILON) {
      for (int j = i; j < n-1; j++) {
	polygon[j] = polygon[j+1];
      }
      n--;
    }
  }

  if (n == 1) {
    hull[0] = polygon[0];
    return 1;
  }

  /* find the first point: min y, and then min x */
  best_i = min_element(polygon, polygon+n) - polygon;
  swap(polygon[0], polygon[best_i]);
  start_p = polygon[0];

  /* find the maximum angle wrt start_p and positive x-axis */
  best_i = 1;
  for (i = 2; i < n; i++) {
    if (ccw_cmp(polygon[best_i], polygon[i])) {
      best_i = i;
    }
  }
  max_p = polygon[best_i];

  /* get simple closed polygon */
  sort(polygon+1, polygon+n, sort_cmp);

  /* do convex hull */
  count = 0;
  hull[count] = polygon[count]; count++;
  hull[count] = polygon[count]; count++;
  for (i = 2; i < n; i++) {
    while (count > 1 &&
           ccw(hull[count-2], hull[count-1], polygon[i]) == CW) {
      /* pop point */
      count--;
    }
    hull[count++] = polygon[i];
  }
  return count;
}

double area_polygon(Point *polygon, int n)
{
  double sum = 0.0;
  int i;

  for (i = 0; i < n-1; i++) {
    sum += polygon[i].x * polygon[i+1].y - polygon[i].y * polygon[i+1].x;
  }
  sum += polygon[n-1].x * polygon[0].y - polygon[n-1].y * polygon[0].x;
  return sum/2.0;
}


int main(void)
{
  int N, n, i, hull_size;
  double rect_area, hull_area;
  double x, y, w, h, j, theta;
  Point p1, v;
  Point polygon[2400], hull[2400];
  double pi = atan(1)*4;
  int k;

  scanf("%d", &N);
  while (N-- > 0) {
    rect_area = 0.0;
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
      scanf("%lf %lf %lf %lf %lf", &x, &y, &w, &h, &j);
      rect_area += w*h;
      theta = j * pi / 180;

      /* p1 is the location of the center of the top edge */
      p1.x = h/2 * sin(theta);
      p1.y = h/2 * cos(theta);

      /* v is the direction to go to get to the corner */
      v.x = w/2 * cos(theta);
      v.y = -w/2 * sin(theta);

      /* get the top two corners */
      polygon[i*4].x   = x + p1.x - v.x;  polygon[i*4].y   = y + p1.y - v.y;
      polygon[i*4+1].x = x + p1.x + v.x;  polygon[i*4+1].y = y + p1.y + v.y;
      
      /* get the bottom corners */
      polygon[i*4+2].x = x - p1.x - v.x;  polygon[i*4+2].y = y - p1.y - v.y;
      polygon[i*4+3].x = x - p1.x + v.x;  polygon[i*4+3].y = y - p1.y + v.y;
      /*      
      for (k = 0; k < 4; k++) {
	printf("(%.1f,%.1f) ", polygon[i*4+k].x, polygon[i*4+k].y);
      }
      printf("\n");
      */
    }

    hull_size = convex_hull(polygon, 4*n, hull);
    hull_area = fabs(area_polygon(hull, hull_size));
    /*
    printf("rect = %.2f, hull = %.2f\n", rect_area, hull_area);
    */
    printf("%.1f %%\n", rect_area*100/hull_area);
  }
  return 0;
}

