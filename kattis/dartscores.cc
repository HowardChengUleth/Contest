#include <bits/stdc++.h>

using namespace std;

void solve()
{
  int n;
  cin >> n;

  int score = 0;
  for (int i = 0; i < n; i++) {
    int x, y;
    cin >> x >> y;
    int dist_sq = x*x + y*y;
    
    for (int p = 10; p >= 1; p--) {
      if (dist_sq <= 20 * 20 * (11-p) * (11-p)) {
	score += p;
	break;
      }
    }
  }

  cout << score << endl;
}

int main()
{
  int T;
  cin >> T;

  for (int i = 0; i < T; i++) {
    solve();
  }

  return 0;
}
