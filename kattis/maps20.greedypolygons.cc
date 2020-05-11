#include <bits/stdc++.h>

using namespace std;

void solve()
{
  int n, l, d, g;
  cin >> n >> l >> d >> g;

  d *= g;

  const double PI = acos(-1.0);
  double ans = PI * d*d;
  ans += n * l * d;

  ans += tan((PI - 2*PI/n)/2) * l*l/4 * n;
  cout << fixed << setprecision(14) << ans << endl;
}

int main()
{
  int N;
  cin >> N;
  while (N--)
    solve();
  
  return 0;
}
