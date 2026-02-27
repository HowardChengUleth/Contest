#include <bits/stdc++.h>

using namespace std;

int N;
int x[11], y[11];

int dist(int x1, int y1, int x2, int y2)
{
  return abs(x1-x2) + abs(y1-y2);
}

int eval(int perm[])
{
  int ans = dist(x[0], y[0], x[perm[0]], y[perm[0]]);
  for (int i = 0; i < N-1; i++) {
    ans += dist(x[perm[i]], y[perm[i]], x[perm[i+1]], y[perm[i+1]]);
  }

  ans += dist(x[perm[N-1]], y[perm[N-1]], x[0], y[0]);
  return ans;
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

  int perm[10];
  iota(perm, perm+N, 1);
  int best = INT_MAX;
  do {
    best = min(best, eval(perm));
   } while (next_permutation(perm, perm+N));

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
