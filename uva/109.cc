/* @JUDGE_ID: 1102NT 109 C "" */

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

int point_in_poly(Point *poly, int n, Point p)
{
  int i, j, c = 0;

  /* first check to see if point is one of the vertices */
  for (i = 0; i < n; i++) {
    if (fabs(p.x - poly[i].x) < EPSILON && 
	fabs(p.y - poly[i].y) < EPSILON) {
      return 0;
    }
  }

  /* now check if it's on the boundary */
  for (i = 0; i < n-1; i++) {
    if (ccw(poly[i], poly[i+1], p) == CNEITHER) {
      return 0;
    }
  }
  if (ccw(poly[n-1], poly[0], p) == CNEITHER) {
    return 0;
  }

  /* finally check if it's inside */
  for (i = 0, j = n-1; i < n; j = i++) {
    if (((poly[i].y - EPSILON <= p.y && p.y < poly[j].y) ||
	 (poly[j].y - EPSILON <= p.y && p.y < poly[i].y)) &&
        (p.x < (poly[j].x - poly[i].x) * (p.y - poly[i].y)
         / (poly[j].y - poly[i].y) + poly[i].x))
      c = !c;
  }
  return c;
}

double area_polygon(Point *polygon, int n)
{
  double sum = 0.0;
  int i;

  for (i = 0; i < n-1; i++) {
    sum += polygon[i].x * polygon[i+1].y - polygon[i].y * polygon[i+1].x;
  }
  sum += polygon[n-1].x * polygon[0].y - polygon[n-1].y * polygon[0].x;
  assert(sum >= 0.0);
  return sum/2.0;
}

#define MAX_KINGDOM 20
#define MAX_VERTICES 100

typedef struct {
  int n;
  Point v[MAX_VERTICES];
  int hit;
} Kingdom;

Kingdom kingdom[MAX_KINGDOM];
int num_kingdoms;

double process_missle(Point p)
{
  int i;
  double sum = 0.0;
  int count = 0;

  for (i = 0; i < num_kingdoms; i++) {
    if (!kingdom[i].hit && point_in_poly(kingdom[i].v, kingdom[i].n, p)) {
      count++;
      sum += fabs(area_polygon(kingdom[i].v, kingdom[i].n));
      kingdom[i].hit = 1;
    }
  }
  assert(sum == 0.0 || count == 1);
  return sum;
}

int main(void)
{
  Point poly[MAX_VERTICES], missle;
  int N;
  int i;
  double area = 0.0;

  num_kingdoms = 0;
  while (scanf("%d", &N) == 1 && N != -1) {
    /* read kingdom */
    for (i = 0; i < N; i++) {
      scanf("%lf %lf", &poly[i].x, &poly[i].y);
    }

    /* compute convex hull */
    kingdom[num_kingdoms].n = convex_hull(poly, N, kingdom[num_kingdoms].v);
    kingdom[num_kingdoms].hit = 0;
    num_kingdoms++;
  }

  /* process missles */
  while (scanf("%lf %lf", &missle.x, &missle.y) == 2) {
    area += process_missle(missle);
  }
  printf("%0.2f\n", area);
  return 0;
}
