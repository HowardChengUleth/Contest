#include <bits/stdc++.h>

using namespace std;

int main()
{
  double D, H;
  cin >> D >> H;

  const double PI = acos(-1.0);
  double theta = 15.0 * PI / 180.0;
  
  double maxH = tan(theta) * D;
  if (H < maxH) {
    cout << "Yes" << endl;
  } else {
    cout << "No" << endl;
  }

  return 0;
}
