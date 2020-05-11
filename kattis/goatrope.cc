#include <bits/stdc++.h>

using namespace std;

double dist(double x1, double y1, double x2, double y2)
{
  return sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
}

double dist(double x, double y, double x1, double y1, double x2, double y2)
{
  double ux = x2-x1, uy = y2-y1;
  double vx = x-x1, vy = y-y1;

  double unorm = sqrt(ux*ux + uy*uy);
  double dot = (ux*vx + uy*vy) / unorm;
  if (0 <= dot && dot <= unorm) {
    return sqrt((vx*vx + vy*vy) - dot*dot);
  } else {
    return min(dist(x,y,x1,y1), dist(x,y,x2,y2));
  }
}

int main()
{
  int x, y, x1, y1, x2, y2;
  cin >> x >> y >> x1 >> y1 >> x2 >> y2;

  double ans = 1e10;
  ans = min(ans, dist(x, y, x1, y1, x1, y2));
  ans = min(ans, dist(x, y, x1, y1, x2, y1));
  ans = min(ans, dist(x, y, x2, y1, x2, y2));
  ans = min(ans, dist(x, y, x1, y2, x2, y2));

  cout << fixed << setprecision(10) << ans << endl;
  
  return 0;
}
