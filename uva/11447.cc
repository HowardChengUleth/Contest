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

using namespace std;

struct Point {
  double x, y;
};

double area_polygon(Point polygon[], int n)
{
  double sum = 0.0;

  for (int i = 0; i < n-1; i++) {
    sum += polygon[i].x * polygon[i+1].y - polygon[i].y * polygon[i+1].x;
  }
  sum += polygon[n-1].x * polygon[0].y - polygon[n-1].y * polygon[0].x;
  return sum/2.0;
}

void solve()
{
  Point poly[10000];
  int N;
  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> poly[i].x >> poly[i].y;
  }
  int W;
  cin >> W;

  double init, used, fall;
  cin >> init >> used >> fall;

  double total = area_polygon(poly, N) * W;
  double V = total * init/100.0;

  // use it
  V -= used;
  if (V < 0) {
    V = 0;
    cout << "Lack of water. ";
  }

  // fill it
  V += fall;
  if (V > total) {
    V = total;
    cout << "Excess of water. ";
  }

  cout << "Final percentage: " << (int)(V/total*100) << "%" << endl;
  
}

int main(void)
{
  int T;
  cin >> T;
  while (T--)
    solve();
  return 0;
}

