#include <bits/stdc++.h>

using namespace std;

void solve()
{
  int n, m;
  cin >> n >> m;

  vector<vector<int>> prize(n);
  vector<int> amount(n);
  for (int i = 0; i < n; i++) {
    int k;
    cin >> k;
    for (int j = 0; j < k; j++) {
      int type;
      cin >> type;
      prize[i].push_back(type-1);
    }
    cin >> amount[i];
  }

  vector<int> sticker(m);
  for (auto &x : sticker) {
    cin >> x;
  }

  int total = 0;
  for (int i = 0; i < n; i++) {
    int num_prizes = INT_MAX;
    for (auto t : prize[i]) {
      num_prizes = min(num_prizes, sticker[t]);
    }
    total += num_prizes * amount[i];
  }
  cout << total << endl;
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
