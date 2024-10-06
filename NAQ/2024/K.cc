#include <bits/stdc++.h>

using namespace std;

int score(int a, int b)
{
  int diff = abs(a-b);

  if (diff <= 15) {
    return 7;
  } else if (diff <= 23) {
    return 6;
  } else if (diff <= 43) {
    return 4;
  } else if (diff <= 102) {
    return 2;
  }

  return 0;
}

int memo[2001][2001];
vector<int> E, A;

// f(i, j) = the max score by matching E[0..i-1] against A[0..j-1]0
int f(int n, int m)
{
  if (n == 0 || m == 0) {
    return 0;
  }

  if (memo[n][m] >= 0) {
    return memo[n][m];
  }

  // if we don't match the last two, then one or the other must be
  // dropped (no need to drop both as it will be considered recursively)
  int ans = max(f(n-1, m), f(n, m-1));

  // or try matching the last two
  ans = max(ans, f(n-1, m-1) + score(E[n-1], A[m-1]));

  return memo[n][m] = ans;
}

int main()
{
  int n, m;
  cin >> n >> m;
  
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      memo[i][j] = -1;
    }
  }

  E.resize(n);
  A.resize(m);

  for (auto &x : E) {
    cin >> x;
  }
  for (auto &x : A) {
    cin >> x;
  }

  cout << f(n, m) << endl;
  
  return 0;
}
