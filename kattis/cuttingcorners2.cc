#include <bits/stdc++.h>

using namespace std;

int main()
{
  int w, h;

  cin >> w >> h;

  double rect = w + h;
  double diag = hypot(w,h);

  cout << fixed << setprecision(10) << rect - diag << endl;

  return 0;
}
