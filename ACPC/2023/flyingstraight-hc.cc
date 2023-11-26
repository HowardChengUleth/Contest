#include <bits/stdc++.h>

using namespace std;

int main()
{
  const double R = 6378137;
  double F, G, T;
  cin >> F >> G >> T;

  double fx = R*cos(G*T/R);
  double fy = R*sin(G*T/R);
  double hx = R;
  double hy = F*T;
  cout << fixed << setprecision(10) << hypot(fx-hx, fy-hy) << endl;

  return 0;
}
