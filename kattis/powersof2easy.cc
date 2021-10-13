#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main()
{
  int n, e;
  cin >> n >> e;

  int ans = 0;
  string p2 = to_string(1 << e);
  for (int k = 0; k <= n; k++) {
    string s = to_string(k);
    ans += (s.find(p2) != string::npos);
  }

  cout << ans << endl;
  return 0;
}
