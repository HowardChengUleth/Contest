#include <bits/stdc++.h>

using namespace std;

// given horizontal line (x1, ly) - (x2, ly), how far is it from (x,y)?
double dist(int x, int y, int x1, int x2, int ly)
{
  if (x1 <= x && x <= x2) {
    return abs(y - ly);
  }

  double dist1 = sqrt((x-x1)*(x-x1) + (y-ly)*(y-ly));
  double dist2 = sqrt((x-x2)*(x-x2) + (y-ly)*(y-ly));

  return min(dist1, dist2);
}

int main()
{
  int x, y, x1, y1, x2, y2;
  cin >> x >> y >> x1 >> y1 >> x2 >> y2;

  double dist1 = dist(x, y, x1, x2, y1);
  double dist2 = dist(x, y, x1, x2, y2);
  double dist3 = dist(y, x, y1, y2, x1);
  double dist4 = dist(y, x, y1, y2, x2);

  double ans = min(min(dist1, dist2), min(dist3, dist4));
  cout << fixed << setprecision(10) << ans << endl;


  return 0;
}
