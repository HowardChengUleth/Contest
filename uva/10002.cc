/* @JUDGE_ID: 1102NT 10002 C "" */

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cassert>
#include <algorithm>

using namespace std;

struct Point {
  double x, y;
  bool operator<(const Point &p) const {
    return y < p.y || (y == p.y && x < p.x);
  }  
};

/* how close to call equal */
const double EPSILON = 1E-8;


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


Point com(Point *polygon, int n)
{
  Point polygon2[100];
  Point ans, p2;
  double area1, area2, area3;
  int i;

  ans.x = (polygon[0].x + polygon[1].x + polygon[2].x)/3.0;
  ans.y = (polygon[0].y + polygon[1].y + polygon[2].y)/3.0;

  if (n > 3) {
    /* take one triangle away */
    polygon2[0] = polygon[0];
    for (i = 2; i < n; i++) {
      polygon2[i-1] = polygon[i];
    }
    
    area1 = fabs(area_polygon(polygon, 3));
    area2 = fabs(area_polygon(polygon2, n-1));
    area3 = area1 + area2;

    p2 = com(polygon2, n-1);

    ans.x = (area1 * ans.x + area2 * p2.x) / area3;
    ans.y = (area1 * ans.y + area2 * p2.y) / area3;
  }
  return ans;
}

int main(void)
{
  Point polygon[100], hull[100], c;
  int n, hull_size;
  int i;

  while (scanf("%d", &n) == 1 && n >= 3) {
    for (i = 0; i < n; i++) {
      scanf("%lf %lf", &polygon[i].x, &polygon[i].y);
    }
    hull_size = convex_hull(polygon, n, hull);
    c = com(hull, hull_size);
    printf("%.3f %.3f\n", c.x, c.y);
  }
  return 0;
}
