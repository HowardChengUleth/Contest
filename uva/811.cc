/*
 * Convex hull
 *
 * Author: Howard Cheng
 * Reference:
 *   http://wilma.cs.brown.edu/courses/cs016/packet/node25.html
 *
 * Given a list of n (n >= 1) points in an array, it returns the vertices of
 * the convex hull in counterclockwise order.  Also returns the number of
 * vertices in the convex hull.  Assumes that the hull array has been
 * allocated to store the right number of elements (n elements is safe).
 * The points in the original polygon will be re-ordered.
 *
 * Note: The hull contains a maximum number of points.  ie. all colinear
 *       points and non-distinct points are included in the hull.
 *
 */

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

double dist(Point a, Point b)
{
  double dx = a.x-b.x, dy = a.y-b.y;
  return sqrt(dx*dx+dy*dy);
}

bool solve(int id)
{
  int n;
  cin >> n;
  if (!n) return false;
  
  Point tree[15];
  int val[15], len[15];
  for (int i = 0; i < n; i++) {
    cin >> tree[i].x >> tree[i].y >> val[i] >> len[i];
  }

  int best_subset;
  int best_val = -1;
  int best_num = -1;
  double best_excess = -1.0;
  for (int s = 1; s < (1 << n); s++) {
    Point poly[15], hull[15];
    int p = 0;
    int len_cut = 0;
    int val_cut = 0;
    for (int i = 0; i < n; i++) {
      if (s & (1 << i)) {
	poly[p++] = tree[i];
      } else {
	val_cut += val[i];
	len_cut += len[i];
      }
    }
    int h = convex_hull(poly, p, hull);
    double peri = 0.0;
    for (int i = 0; i < h; i++) {
      peri += dist(hull[i], hull[(i+1)%h]);
    }
    if (len_cut < peri) continue;
    if (best_val == -1 ||
	(val_cut < best_val) ||
	(val_cut == best_val && n-p < best_num)) {
      best_subset = s;
      best_val = val_cut;
      best_num = n-p;
      best_excess = len_cut - peri;
    }
  }

  if (id > 1) cout << endl;
  cout << "Forest " << id << endl;
  cout << "Cut these trees:";
  for (int i = 0; i < n; i++) {
    if (!(best_subset & (1 << i))) {
      cout << ' ' << i+1;
    }
  }
  cout << endl;
  cout << "Extra wood: " << fixed << setprecision(2) << best_excess << endl;
  
  return true;
}

int main(void)
{
  int id = 1;
  while (solve(id++))
    ;
  return 0;
}
