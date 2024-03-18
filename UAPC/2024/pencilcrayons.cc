#include <bits/stdc++.h>

using namespace std;

int main()
{
  int n, k;
  int ans = 0;
  
  cin >> n >> k;
  for (int i = 0; i < n; i++) {
    map<string, int> M;
    for (int j = 0; j < k; j++) {
      string s;
      cin >> s;
      M[s]++;
    }
    for (auto [s, c] : M) {
      ans += (c-1);
    }
  }

  cout << ans << endl;
  return 0;
}
