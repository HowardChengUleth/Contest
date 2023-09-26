#include <bits/stdc++.h>

using namespace std;

int n;
bool reachable[4][30];

int solve(int covered[], int wall)
{
  if (wall >= 4) {
    // all walls are covered
    return 0;
  }

  if (covered[wall]) {
    // this wall is already covered
    return solve(covered, wall+1);
  }

  int ans = 4 - wall;    // worst case
  for (int i = 0; i < n; i++) {
    if (reachable[wall][i]) {
      // try this crane
      for (int w = 0; w < 4; w++) {
	covered[w] += reachable[w][i];
      }

      ans = min(ans, 1 + solve(covered, wall+1));
      
      for (int w = 0; w < 4; w++) {
	covered[w] -= reachable[w][i];
      }
    }
  }

  return ans;
}

int main()
{
  int l, w, r;
  cin >> l >> w >> n >> r;

  // double everything so we stay in integers
  l *= 2;
  w *= 2;
  r *= 2;

  int x[30], y[30];
  for (int i = 0; i < n; i++) {
    cin >> x[i] >> y[i];
    x[i] *= 2;
    y[i] *= 2;
  }

  int wx[4] = { -l/2, l/2, 0, 0 };
  int wy[4] = { 0, 0, -w/2, w/2 };
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < n; j++) {
      int dx = wx[i] - x[j];
      int dy = wy[i] - y[j];
      reachable[i][j] = ((dx*dx + dy*dy) <= r*r);
    }
  }

  for (int i = 0; i < 4; i++) {
    if (count(reachable[i], reachable[i]+n, true) == 0) {
      cout << "Impossible" << endl;
      return 0;
    }
  }

  int covered[4] = {0};
  cout << solve(covered, 0) << endl;
  
  
  return 0;
}
