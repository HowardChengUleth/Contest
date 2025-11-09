#include <bits/stdc++.h>

using namespace std;

const int MAX_HOURS = 1000;
const int MAX_M = 10;
const int MAX_B = 20;

int N, M, B;
vector<int> p, r, s;
vector<vector<int>> c, d;

int64_t memo[MAX_HOURS+1][MAX_B+1];
bool seen[MAX_HOURS+1][MAX_B+1];

// f(n, b) = min cost to operate first n hours, and end with battery level b
//           INT_MAX if impossible
int64_t f(int n, int b)
{
  if (n == 0) {
    return (b == 0) ? 0 : INT_MAX;
  }

  if (seen[n][b]) {
    return memo[n][b];
  }
  
  int64_t &ans = memo[n][b];
  ans = INT_MAX;

  for (int b2 = 0; b2 <= B; b2++) {
    // decide how much battery to use (neg means you need to store)
    int battery_use = b2 - b;

    // how much power is really required (could be negative)
    int required = r[n-1] - battery_use - s[n-1];

    // how much power do we want to sell (rest goes to waste)
    for (int j = 0; j < M; j++) {
      int64_t cost = f(n-1, b2);
      int power_import = required + d[n-1][j];
      if (power_import >= 0) {
	cost += power_import * p[n-1];
      }
      cost -= c[n-1][j];
      ans = min(ans, cost);
    }
  }

  seen[n][b] = true;

  return ans;

}

int main()
{
  cin >> N >> M >> B;
  p.resize(N);
  r.resize(N);
  s.resize(N);

  for (int i = 0; i < N; i++) {
    cin >> p[i] >> r[i] >> s[i];
  }

  // introduce a fake plan at the end of (0,0)
  c.resize(N);
  for (int i = 0; i < N; i++) {
    c[i].resize(M+1);
    for (int j = 0; j < M; j++) {
      cin >> c[i][j];
    }
    c[i][M] = 0;
  }
  d.resize(N);
  for (int i = 0; i < N; i++) {
    d[i].resize(M+1);
    for (int j = 0; j < M; j++) {
      cin >> d[i][j];
    }
    d[i][M] = 0;
  }
  M++;
  

  int64_t mincost = INT_MAX;
  for (int b = 0; b <= B; b++) {
    mincost = min(mincost, f(N, b));
  }

  cout << mincost << endl;

  // no point of having any leftover batteries at the end
  assert(mincost == f(N, 0));

  return 0;
}
