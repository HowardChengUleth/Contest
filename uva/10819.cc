#include <iostream>

using namespace std;

bool solve()
{
  int m, n;
  if (!(cin >> m >> n)) return false;

  int p[100], f[100];
  for (int i = 0; i < n; i++) {
    cin >> p[i] >> f[i];
  }

  int best[101][10201];

  for (int i = 0; i <= n; i++) {
    fill(best[i], best[i]+10201, -1);
  }
  best[0][0] = 0;

  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < 10201; j++) {
      if (best[i-1][j] < 0) continue;

      // don't buy item i-1
      best[i][j] = max(best[i][j], best[i-1][j]);

      // buy item i-1
      int newamt = j + p[i-1];
      if (newamt >= 10200) continue;
      best[i][newamt] = max(best[i][newamt], best[i-1][j] + f[i-1]);
    }
  }

  int ans = 0;
  for (int j = 0; j < 10201; j++) {
    if (best[n][j] < 0) continue;
    if (j <= 2000 && j > m) continue;
    if (j > 2000 && j > m+200) continue;
    ans = max(ans, best[n][j]);
  }
  cout << ans << endl;
  return true;
}

int main(void)
{
  while (solve())
    ;
  return 0;
}
