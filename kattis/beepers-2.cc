#include <bits/stdc++.h>

using namespace std;

int N;
int x[11], y[11];

int dist(int i, int j)
{
  return abs(x[i]-x[j]) + abs(y[i]-y[j]);
}

// start at v and end at 0, and vset is the bitset of unvisited
// vertices
int memo[11][2048];

int f(int v, int vset)
{
  if (vset == (1 << (N+1)) - 2) {
    return dist(v, 0);
  }

  int &ans = memo[v][vset];
  if (ans >= 0) {
    return ans;
  }
  
  int best = INT_MAX;
  for (int w = 1; w <= N; w++) {
    if ((1 << w) & vset) continue;   // already visited
    best = min(best, f(w, vset | (1 << w)) + dist(v, w));
  }

  return ans = best;
}

void solve()
{
  int X, Y;
  cin >> X >> Y;
  
  cin >> x[0] >> y[0];

  cin >> N;
  for (int i = 1; i <= N; i++) {
    cin >> x[i] >> y[i];
  }

  for (int i = 1; i <= N; i++) {
    fill(memo[i], memo[i] + (1 << (N+1)), -1);
  }
  int best = INT_MAX;
  for (int i = 1; i <= N; i++) {
    best = min(best, f(i, (1 << i)) + dist(0, i));
  }
  
  cout << best << endl;
}

int main()
{
  int N;
  cin >> N;
  for (int i = 0; i < N; i++) {
    solve();
  }

  return 0;
}
