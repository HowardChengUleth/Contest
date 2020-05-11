#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;


/* how close to call equal */
const double EPSILON = 1E-8;

struct Point {
  double x, y;
};

int circle(Point p1, Point p2, Point p3, Point &center, double &r)
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
  center.x = (d*e - b*f) / g;
  center.y = (a*f - c*e) / g;
  r = sqrt((p1.x-center.x)*(p1.x-center.x) + (p1.y-center.y)*(p1.y-center.y));
  return 1;
}

double dist(Point p, Point q)
{
  double dx = p.x-q.x, dy = p.y-q.y;
  return sqrt(dx*dx + dy*dy);
}

int C3(int n)
{
  return (n*(n-1)*(n-2)/6);
}

bool solve()
{
  int N;
  cin >> N;
  if (!N) return false;

  Point p[100];
  for (int i = 0; i < N; i++) {
    cin >> p[i].x >> p[i].y;
  }

  int best = 0;
  for (int i = 0; i < N; i++) {
    for (int j = i+1; j < N; j++) {
      for (int k = j+1; k < N; k++) {
	Point center;
	double r;
	if (!circle(p[i], p[j], p[k], center, r)) continue;

	int c = 0;
	for (int ii = 0; ii < N; ii++) {
	  if (fabs(dist(p[ii], center) - r) < EPSILON) c++;
	}
	best = max(best, c);
      }
    }
  }

  if (best == 0) {
    best = min(2, N);
  }
  cout << best << endl;
  
  return true;
}

int main()
{
  while (solve())
    ;
  
  return 0;
}
