// The idea is that we will look at each tower and see how much it covers
// that has not already been covered.  The way to do this is that for each
// tower, we transform to polar coordinates about the center of that circle.
// Then we shoot rays from the origin to see how far it goes.  As the
// angle varies, this sweeps out a function r = f(theta) and the area under
// the curve is the area that we want.

#include <iostream>
#include <cmath>
#include <iomanip>
#include <algorithm>

using namespace std;

int N;
double x[25], y[25], r[25];

const double PI = acos(-1.0);


// to intersect a ray from tower t at angle theta with area for tower k:
//
// -   we find the unit vector (vx, vy) defining the ray from tower t
// -   the ray is then given as (x[t] + s*vx, y[t] + s*vy) for s >= 0
// -   we want to find a point on this ray where distance to tower k is
//     r[k]
// -   letting dx = x[t] - x[k], dy = y[t] - y[k], a bit of algebra shows
//     that
//
//        0 = s^2 + 2*(dx*vx + dy*vy)*s + dx^2 + dy^2 - r[k]^2
double find_intersect(int t, double theta, int k)
{
  double dx = x[t] - x[k], dy = y[t] - y[k];
  double vx = cos(theta), vy = sin(theta);

  double a = 1, b = 2*(dx*vx + dy*vy), c = dx*dx + dy*dy - r[k]*r[k];

  double disc = b*b - 4*a*c;
  if (disc < 0) return -1;

  double root1 = (-b + sqrt(disc))/(2*a);
  double root2 = (-b - sqrt(disc))/(2*a);

  if (root1 < 0) return -1;
  if (root2 < 0) return root1;
  return root2;
}


// find the area covered by tower t inside the area, that is not already
// covered by towers 1..t-1
//
// To find the area, compute the integral
//
//     Int(Int(r, r = 0..h(theta)), theta=0..2*PI)
//   = Int(h(theta)^2/2, theta=0..2*PI)
//
// where h(theta) is the closest intersecting previous tower (or the total
// area).  We integrate with trapezoid rule.

const int STEPS = 10000;
double f[STEPS+1];    // h(theta)^2/2

double find_covered(int t)
{
  for (int i = 0; i <= STEPS; i++) {
    double theta = i*2*PI / STEPS;

    f[i] = r[t];
    for (int j = 0; j < t; j++) {
      double temp = find_intersect(t, theta, j);
      if (temp >= 0) {
	f[i] = min(f[i], temp);
      }
    }
    f[i] = f[i] * f[i] / 2.0;
  }

  double area = 0.0;
  for (int i = 0; i < STEPS; i++) {
    area += (f[i] + f[i+1]);
  }
  area *= PI / STEPS;

  return area;
}

int main(void)
{
  while (cin >> N && N > 0) {
    double total, covered = 0.0;
    for (int i = 0; i < N; i++) {
      cin >> x[i] >> y[i] >> r[i];
    }

    total = PI*r[0]*r[0];

    for (int i = 1; i < N; i++) {
      covered += find_covered(i);
    }

    cout << fixed << setprecision(2) << covered/total << endl;
  }
  return 0;
}
