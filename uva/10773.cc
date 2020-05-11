#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main()
{
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cout << "Case " << i << ": ";
    double d, v, u;
    cin >> d >> v >> u;

    if (u <= v || u == 0 || v == 0) {
      cout << "can't determine" << endl;
    } else {
      double t1 = d/u;
      double t2 = d/sqrt(u*u-v*v);
      cout << fixed << setprecision(3) << t2-t1 << endl;
    }
  }
  return 0;
}
  
