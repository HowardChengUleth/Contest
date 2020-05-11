#include <iostream>
#include <algorithm>

using namespace std;

void solve()
{
  int n, b, c;
  cin >> n >> b >> c;

  int grid[101] = {0};
  while (b--) {
    int f, t;
    cin >> f >> t;
    grid[f] = t;
  }

  bool gameover = false;
  int player[1000000];
  fill(player, player+n, 1);
  int p = 0;

  while (c--) {
    int roll;
    cin >> roll;
    if (gameover) continue;
    player[p] += roll;
    if (player[p] > 100) player[p] = 100;
    if (grid[player[p]]) player[p] = grid[player[p]];
    if (player[p] == 100) gameover = true;
    if (++p == n) p = 0;
  }
  for (int i = 0; i < n; i++) {
    cout << "Position of player " << i+1 << " is " << player[i] << '.' << endl;
  }
}

int main(void)
{
  int T;
  cin >> T;
  while (T--) {
    solve();
  }
  return 0;
}
