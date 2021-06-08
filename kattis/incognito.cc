#include <bits/stdc++.h>

using namespace std;

void solve()
{
  map<string,int> freq;

  int n;
  cin >> n;
  while (n--) {
    string name, cat;
    cin >> name >> cat;
    freq[cat]++;
  }

  int ans = 1;
  for (auto [cat, f] : freq) {
    ans *= f+1;
  }

  cout << ans-1 << endl;
}

int main()
{
  int T;
  cin >> T;

  while (T--) {
    solve();
  }

  return 0;
}
