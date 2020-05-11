#include <bits/stdc++.h>

using namespace std;

void solve(int n, const string &s)
{
  string init[6] = {"RGB", "RBG", "GRB", "GBR", "BGR", "BRG"};

  int ans = 2*n;
  string best;

  for (int i = 0; i < 6; i++) {
    int cost = 0;
    string soln(n, ' ');
    for (int k = 0; k < n; k++) {
      soln[k] = init[i][k%3];
      cost += soln[k] != s[k];
    }
    if (cost < ans) {
      ans = cost;
      best = soln;
    }
  }

  cout << ans << endl << best << endl;
}

int main()
{
  int n;
  string s;
  cin >> n >> s;

  if (n == 1) {
    cout << 0 << endl << s << endl;
  } else if (n == 2) {
    if (s[0] != s[1]) {
      cout << 0 << endl << s << endl;
    } else {
      s[0] = (s[0] == 'R') ? 'G' : 'R';
      cout << 1 << endl << s << endl;
    }
  } else {
    solve(n, s);
  }
  
  return 0;
}
