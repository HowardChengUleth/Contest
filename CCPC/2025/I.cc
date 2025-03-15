#include <bits/stdc++.h>

using namespace std;

const double PI = acos(-1.0);

int main()
{
  double theta, v, dmin, dmax;
  cin >> theta >> v >> dmin >> dmax;

  theta *= PI/180.0;

  double vx = v * cos(theta);
  double vy = v * sin(theta);

  // time to reach max height: h'(t) = 0
  double t_max = vy / 9.81;

  // time to reach the same height
  double t = t_max * 2.0;

  // distance travelled
  double dist = t * vx;

  if (dmin <= dist && dist <= dmax) {
    cout << "POSSIBLE" << endl;
  } else {
    cout << "IMPOSSIBLE" << endl;
  }
  
  


  return 0;
}
