#include <bits/stdc++.h>

using namespace std;

int K, M;
vector<int> c;

int cost(int h)
{
  // could use cumulative sum to be more efficient...

  int bricks_per_layer = (K + (h-1)) / h;

  int ans = 0;
  for (int i = 0; i < h; i++) {
    ans += bricks_per_layer * c[i];
  }

  return ans;
}

int main()
{
  cin >> K >> M;
  c.resize(M);
  for (auto &x : c) {
    cin >> x;
  }

  int best = INT_MAX;
  for (int h = 1; h <= M; h++) {
    best = min(best, cost(h));
  }

  cout << best << endl;

  return 0;
}
