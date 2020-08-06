#include <bits/stdc++.h>

// just do it...

using namespace std;

int main()
{
  double C;
  int L;

  cin >> C >> L;

  double ans = 0.0;
  for (int i = 0; i < L; i++) {
    double w, l;
    cin >> w >> l;
    ans += C * w * l;
  }

  cout << fixed << setprecision(10) << ans << endl;

  return 0;
}
