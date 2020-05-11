/* @JUDGE_ID: 1102NT 10456 C "" */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <stdio.h>
#include <assert.h>


int gcd(int a, int b)
{
  int r;

  /* unnecessary if a, b >= 0 */
  if (a < 0) {
    a = -a;
  }
  if (b < 0) {
    b = -b;
  }

  while (b) {
    r = a % b;
    a = b;
    b = r;
  }
  assert(a >= 0);
  return a;
}

void reduce(int *a, int *b)
{
  int g = gcd(*a, *b);

  *a /= g;
  *b /= g;
  if (*b < 0) {
    *a *= -1;
    *b *= -1;
  }
}

#define MAX_N 30

typedef struct {
  int x, y;
} Point;

int between(Point a, Point b, Point c)
{
  int dx1 = b.x - a.x;
  int dx2 = c.x - b.x;
  int dy1 = b.y - a.y;
  int dy2 = c.y - b.y;
  int t1 = dy2 * dx1;
  int t2 = dy1 * dx2;

  if ((a.x == c.x && a.y == c.y) || (b.x == c.x && b.y == c.y)) {
    return 1;
  }
  
  if (t1 == t2) {
    return (((dx1 * dx2 < 0 || dy1 * dy2 < 0)) &&
	    (dx1*dx1 + dy1*dy1 >= dx2*dx2 + dy2*dy2));
  } else {
    return 0;
  }
}

int area_polygon2(Point *polygon, int n)
{
  int sum = 0;
  int i;

  for (i = 0; i < n-1; i++) {
    sum += polygon[i].x * polygon[i+1].y - polygon[i].y * polygon[i+1].x;
  }
  sum += polygon[n-1].x * polygon[0].y - polygon[n-1].y * polygon[0].x;
  return abs(sum);
}

int read_poly(Point *poly)
{
  int n, i;
  if (scanf("%d", &n) != 1) {
    return 0;
  }

  for (i = 0; i < n; i++) {
    scanf("%d %d", &poly[i].x, &poly[i].y);
  }

  return n;
}

void solve(Point *poly, int n, Point p)
{
  Point hull[MAX_N+1];
  int i, j, pi;
  int A2 = area_polygon2(poly, n);
  int tA, diff;
  int xn, xd, yn, yd;

  for (pi = 1; pi < n; pi++) {
    if (between(poly[pi-1], poly[pi], p)) {
      break;
    }
  }
  if (pi == n) {
    assert(between(poly[0], poly[n-1], p));
  }
  j = 0;
  hull[j++] = p;
  i = pi % n;
  do {
    hull[j++] = poly[i];
    i = (i+1) % n;
  } while (i != pi % n);

  for (j = 3; (diff = 2*area_polygon2(hull, j)- A2) < 0; j++)
    ;
  
  if (!diff) {
    xn = hull[j-1].x;  xd = 1;
    yn = hull[j-1].y;  yd = 1;
  } else {
    tA = area_polygon2(hull,j) - area_polygon2(hull, j-1);
    xn = 2*tA*hull[j-1].x + diff*(hull[j-2].x-hull[j-1].x);
    yn = 2*tA*hull[j-1].y + diff*(hull[j-2].y-hull[j-1].y);
    xd = yd = 2*tA;

    reduce(&xn, &xd);
    reduce(&yn, &yd);

  }
  printf("(%d/%d),(%d/%d)\n", xn, xd, yn, yd);

}

int main(void)
{
  int m, n;
  Point poly[MAX_N+1], p;

  while (n = read_poly(poly)) {
    scanf("%d", &m);
    while (m-- > 0) {
      scanf("%d %d", &p.x, &p.y);
      solve(poly, n, p);
    }
  }

  return 0;
}
