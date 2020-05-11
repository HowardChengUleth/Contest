#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

//
// We want to find (x,y) minimizing
//
//   f(x,y) = sum_{i=1}^N sqrt((x-xi)^2 + (y-yi)^2)
//
// The centroid is a good place to start, and we will use gradient
// descent.
//

double f(int N, int cx[], int cy[], double x, double y)
{
  double ans = 0.0;
  
  for (int i = 0; i < N; i++) {
    ans += sqrt((x-cx[i])*(x-cx[i]) + (y-cy[i])*(y-cy[i]));
  }
  return ans;
}

void gradient(int N, int cx[], int cy[], double x, double y, 
	      double &dx, double &dy)
{
  dx = dy = 0.0;
  
  for (int i = 0; i < N; i++) {
    double denom = sqrt((x-cx[i])*(x-cx[i]) + (y-cy[i])*(y-cy[i]));
    dx += (x - cx[i])/denom;
    dy += (y - cy[i])/denom;
  }
}

void solve()
{
  int N;
  int cx[100], cy[100];
  double x, y;

  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> cx[i] >> cy[i];
    x += cx[i];
    y += cy[i];
  }
  x /= N;
  y /= N;

  double step = 1;
  double best = f(N, cx, cy, x, y);

  while (step > 1e-8) {
    double dx, dy;
    gradient(N, cx, cy, x, y, dx, dy);
    double nx = x - step * dx;
    double ny = y - step * dy;
    double ndist = f(N, cx, cy, nx, ny);
    if (ndist < best) {
      best = ndist;
      x = nx;
      y = ny;
    } else {
      step *= 0.95;
    }
  }
  
  cout << fixed << setprecision(0) << best << endl;

}

int main(void)
{
  int T;
  
  cin >> T;
  while (T-- > 0) {
    solve();
    if (T) cout << endl;
  }
  return 0;
}
