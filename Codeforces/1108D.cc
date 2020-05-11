#include <bits/stdc++.h>

using namespace std;

const string color = "RGB";

int memo[3][200001];
int best[3][200001];
int n;
string s;


// min number for s[k..n-1] if s[k] has color c
int f(int c, int k)
{
  if (k == n-1) {
    return color[c] != s[k];
  }
  if (memo[c][k] >= 0) {
    return memo[c][k];
  }

  memo[c][k] = 2*n;
  for (int c2 = 0; c2 < 3; c2++) {
    if (c == c2) continue;
    int cost = f(c2, k+1) + (color[c] != s[k]);
    if (cost < memo[c][k]) {
      best[c][k] = c2;
      memo[c][k] = cost;
    }
  }

  return memo[c][k];
}

void trace(int c)
{
  for (int i = 0; i < n; i++) {
    cout << color[c];
    c = best[c][i];
  }
  cout << endl;
}

int main()
{
  cin >> n >> s;

  for (int c = 0; c < 3; c++) {
    fill(memo[c], memo[c]+n, -1);
  }

  int ans = 2*n;
  int start;
  for (int c = 0; c < 3; c++) {
    if (f(c, 0) < ans) {
      ans = f(c, 0);
      start = c;
    }
  }
  cout << ans << endl;
  trace(start);

  return 0;
}
