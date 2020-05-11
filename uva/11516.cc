#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cmath>

using namespace std;

bool possible(int *house, int m, int n, double dist)
{
  if (m == 0) {
    return true;
  }
  if (n == 0) {
    return false;
  }

  double ap_loc = house[0] + dist;
  int i;
  for (i = 0; i < m && fabs(house[i] - ap_loc) <= dist+1e-8; i++) 
    ;
  return possible(house+i, m-i, n-1, dist);
}

void solve_case(void)
{
  int n, m;
  int house[100000];

  cin >> n >> m;
  for (int i = 0; i < m; i++) {
    cin >> house[i];
  }
  sort(house, house+m);

  double lo = 0, hi = 1000000;
  while (hi - lo >= 0.01) {
    double mid = (lo + hi) / 2.0;
    if (possible(house, m, n, mid)) {
      hi = mid;
    } else {
      lo = mid;
    }
  }
  
  cout << fixed << setprecision(1) << (lo+hi)/2.0 << endl;

}

int main(void)
{
  int T;
  cin >> T;
  while (T-- > 0) {
    solve_case();
  }

  return 0;
}
