#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;


ull f(ull a, ull b, ull c)
{
  return a*a + b*b + c*c + 7*min(min(a,b),c);
}

void solve()
{
  ull a, b, c, d;
  cin >> a >> b >> c >> d;
  if (a < b) swap(a, b);
  if (a < c) swap(a, c);

  ull ans = f(a+d, b, c);
  for (int aa = 0; aa <= d && aa <= 7; aa++) {
    for (int bb = 0; bb <= d-aa && bb <= 7; bb++) {
      int cc = d - bb - aa;
      ans = max(ans, f(a+aa, b+bb, c+cc));
    }
  }
  
  cout << ans << endl;
}

int main()
{
  int N;
  cin >> N;
  while (N--) {
    solve();
  }

  return 0;
}
