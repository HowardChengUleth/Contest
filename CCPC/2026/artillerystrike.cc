// look at all pair of points, and each pair determines two circles going
// through that pair.  Check all other points to see if they are inside
// these circles.
//
//  O(N^3)
//

#include <iostream>
#include <sstream>
#include <cmath>

using namespace std;

const double EPS = 1e-8;

int count_pts(double cx, double cy, int x[], int y[], int n, int R)
{
  int count = 0;
  for (int i = 0; i < n; i++) {
    double dx = cx - x[i], dy = cy - y[i];
    if (dx*dx + dy*dy <= R*R + EPS) {
      count++;
    }
  }
  return count;
}

int count(int x[], int y[], int n, int i, int j, int R)
{
  double dx = x[i] - x[j], dy = y[i] - y[j];
  int dist_sq = dx * dx + dy * dy;
  double mx = (x[i] + x[j])/2.0, my = (y[i] + y[j])/2.0;

  int temp_int = 4*R*R - dist_sq;
  double temp = R*R - dist_sq/4.0;
  if (temp_int < 0) {
    return 0;
  }

  dx /= sqrt(dist_sq);
  dy /= sqrt(dist_sq);
  dx *= sqrt(temp);
  dy *= sqrt(temp);

  return max(count_pts(mx - dy, my + dx, x, y, n, R),
	     count_pts(mx + dy, my - dx, x, y, n, R));
}

int main(void)
{
  int x[200], y[200];
  int n, R;

  cin >> n >> R;
    
  for (int i = 0; i < n; i++) {
    cin >> x[i] >> y[i];
  }
  
  int best = 1;
  for (int i = 0; i < n; i++) {
    best = max(best, count_pts(x[i], y[i], x, y, n, R));
    for (int j = i+1; j < n; j++) {
      if (x[i] == x[j] && y[i] == y[j]) continue;
      best = max(best, count(x, y, n, i, j, R));
    }
  }
  
  cout << best << endl;

  return 0;
}
