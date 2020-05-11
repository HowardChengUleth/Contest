/*
 * Area of a polygon
 *
 * Author: Howard Cheng
 * Reference:
 *   http://www.exaflop.org/docs/cgafaq/cga2.html
 *
 * This routine returns the SIGNED area of a polygon represented as an
 * array of n points (n >= 1).  The result is positive if the orientation is
 * counterclockwise, and negative otherwise.
 *
 */

#include <iostream>
#include <iomanip>
#include <cmath>
#include <cassert>
#include <algorithm>

using namespace std;

struct Point {
  int x, y;
  
  bool operator<(const Point &p) const {
    return y < p.y || (y == p.y && x < p.x);
  }
      
};

// returns 2*area.
int area_polygon(Point polygon[], int n)
{
  int sum = 0;

  for (int i = 0; i < n-1; i++) {
    sum += polygon[i].x * polygon[i+1].y - polygon[i].y * polygon[i+1].x;
  }
  sum += polygon[n-1].x * polygon[0].y - polygon[n-1].y * polygon[0].x;
  return sum;
}

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


/* counterclockwise, clockwise, or undefined */
enum Orientation {CCW, CW, CNEITHER};

/* Global point for computing convex hull */
Point start_p, max_p; 

bool colinear(Point a, Point b, Point c)
{
  int dx1 = b.x - a.x;
  int dx2 = c.x - b.x;
  int dy1 = b.y - a.y;
  int dy2 = c.y - b.y;
  int t1 = dy2 * dx1;
  int t2 = dy1 * dx2;
  return t1 == t2;
}

Orientation ccw(Point a, Point b, Point c)
{
  int dx1 = b.x - a.x;
  int dx2 = c.x - b.x;
  int dy1 = b.y - a.y;
  int dy2 = c.y - b.y;
  int t1 = dy2 * dx1;
  int t2 = dy1 * dx2;

  if (t1 == t2) {
    if (dx1 * dx2 < 0 || dy1 * dy2 < 0) {
      if (dx1*dx1 + dy1*dy1 >= dx2*dx2 + dy2*dy2) {
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
    int dx1 = abs(start_p.x - a.x);
    int dx2 = abs(start_p.x - b.x);
    int dy1 = abs(start_p.y - a.y);
    int dy2 = abs(start_p.y - b.y);
    return dx1 > dx2 || (dx1 == dx2 && dy1 > dy2);
  } else {
    return ccw(start_p, a, b) == CCW;
  }
}

int convex_hull(Point polygon[], int n, Point hull[]) {
  int count, best_i, i;

  sort(polygon, polygon+n);
  for (int i = n-1; i >= 1; i--) {
    if (polygon[i].x == polygon[i-1].x &&
	polygon[i].y == polygon[i-1].y) {
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

int get_hull(Point hull[], char grid[100][100], int nr, int nc)
{
  Point poly[10000];
  int n = 0;
  for (int i = 0; i < nr; i++) {
    for (int j = 0; j < nc; j++) {
      if (grid[i][j] == '1') {
	poly[n].y = i;
	poly[n].x = j;
	n++;
      }
    }
  }

  int h = convex_hull(poly, n, hull);
  return h;
}

bool do_case(int id)
{
  int nr, nc;
  double T;

  cin >> nr >> nc >> T;
  if (!nr && !nc && T == 0.0) return false;

  char grid[100][100];
  
  for (int i = 0; i < nr; i++) {
    for (int j = 0; j < nc; j++) {
      cin >> grid[i][j];
    }
  }

  Point hull[10000];
  int h = get_hull(hull, grid, nr, nc);

  int total_area = area_polygon(hull, h);
  
  cout << "Case " << id << ":" << endl;
  
  bool done = false;
  int removed = 0;
  while (!done) {
    done = true;
    int best_area = total_area + 1;
    int best = -1;

    for (int i = 0; i < h; i++) {
      int r = hull[i].y;
      int c = hull[i].x;

      grid[r][c] = '0';
      Point newhull[10000];
      int newh = get_hull(newhull, grid, nr, nc);
      int area = area_polygon(newhull, newh);
      grid[r][c] = '1';

      if (area < best_area ||
	  (area == best_area &&
	   (r < hull[best].y || (r == hull[best].y && c < hull[best].x)))) {
	best_area = area;
	best = i;
      }
    }

    if ((total_area - best_area)*100.0/total_area >= T) {
      cout << "   Delete pixel at (" << hull[best].y << ","
	   << hull[best].x << ")" << endl;
      done = false;
      grid[hull[best].y][hull[best].x] = '0';
      h = get_hull(hull, grid, nr, nc);
      total_area = area_polygon(hull, h);
      removed++;
    }
  }

  if (!removed) {
    cout << "   No pixels deleted." << endl;
  }
  return true;
}

int main()
{
  int case_num = 1;
  while (do_case(case_num++))
    ;
  return 0;
}
