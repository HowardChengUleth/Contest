#include <bits/stdc++.h>

using namespace std;

// once we mark off all the spots that are unavailable based on the given
// string, it is sufficient to greedily choose the leftmost available spot
// repeatedly

void solve()
{
  int n, k;
  string s;
  cin >> n >> k >> s;

  vector<bool> bad(n, false);

  int counter = 0;
  for (int i = 0; i < n; i++) {
    if (s[i] == '1') {
      counter = k+1;
    }
    if (counter > 0) {
      bad[i] = true;
      counter--;
    }
  }
  counter = 0;
  for (int i = n-1; i >= 0; i--) {
    if (s[i] == '1') {
      counter = k+1;
    }
    if (counter > 0) {
      bad[i] = true;
      counter--;
    }
  }

  int ans = 0;
  int i = 0;
  while (i < n) {
    if (bad[i]) {
      i++;
    } else {
      ans++;
      i += k+1;
    }
  }

  cout << ans << endl;
}

int main()
{
  int t;
  cin >> t;
  while (t--) {
    solve();
  }

  return 0;
}
