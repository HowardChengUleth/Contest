#include <bits/stdc++.h>

using namespace std;


int n;
vector<int> c;

int memo[30001][101];
int menu[30001][101];

// number of ways to form sum s, using c[k..n-1]
int ways(int s, int k)
{
  if (s < 0)
    return 0;
  if (s == 0)
    return 1;

  int &ans = memo[s][k];
  if (ans != -1) {
    return ans;
  }

  ans = 0;
  for (int i = k; i < n; i++) {
    int temp = ways(s - c[i], i);
    if (temp == 1) {
      menu[s][k] = i;
    }
    ans = min(2, ans + temp);
  }
  return ans;
}


void solve()
{
  int s;
  cin >> s;

  int t = ways(s, 0);
  if (t == 0) {
    cout << "Impossible" << endl;
  } else if (t > 1) {
    cout << "Ambiguous" << endl;
  } else {
    int k = 0;
    while (s > 0) {
      k = menu[s][k];
      cout << k+1 << ' ';
      s -= c[k];
    }
    cout << endl;
  }
}

int main()
{
  cin >> n;
  c.resize(n);
  for (auto &x : c) {
    cin >> x;
  }

  for (int s = 0; s <= 30000; s++) {
    for (int i = 0; i <= n; i++) {
      memo[s][i] = -1;
    }
  }

  int m;
  cin >> m;

  while (m--) {
    solve();
  }
  
  return 0;
}
