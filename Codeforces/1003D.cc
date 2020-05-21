#include <bits/stdc++.h>

using namespace std;

// All coins are powers of 2.  We want to minimize the number of coins,
// so we can do things greedily by using as many of the big ones as possible.

map<int, int> coin;

int solve(int b)
{
  int ans = 0;
  for (auto it = rbegin(coin); it != rend(coin); ++it) {
    int val = it->first;
    int freq = it->second;
    int use = min(b / val, freq);
    ans += use;
    b -= use * val;
  }

  if (b)
    return -1;
  else
    return ans;
}

int main()
{
  int n, q;
  cin >> n >> q;

  for (int i = 0; i < n; i++) {
    int a;
    cin >> a;
    coin[a]++;
  }

  for (int i = 0; i < q; i++) {
    int b;
    cin >> b;
    cout << solve(b) << endl;
  }


  return 0;
}
