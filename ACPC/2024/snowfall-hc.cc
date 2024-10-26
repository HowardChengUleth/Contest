#include <bits/stdc++.h>

using namespace std;

int main()
{
  int n;
  cin >> n;

  int ans = 0;
  for (int i = 0; i < n; i++) {
    int t, a;
    cin >> t >> a;
    if (t) {
      ans = max(0, ans-a);
    } else {
      ans += a;
    }
  }

  cout << ans << endl;

  return 0;
}
