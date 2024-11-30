#include <bits/stdc++.h>

using namespace std;

int main()
{
  int n, c, p;
  cin >> n >> c >> p;

  int ans = 0;
  for (int i = 0; i < n; i++) {
    int val;
    cin >> val;
    if (val > c + p) {
      ans++;
      p = c;
      c = val;
    }
  }
  cout << ans << endl;
  return 0;
}
