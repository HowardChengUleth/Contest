#include <bits/stdc++.h>

using namespace std;

int main()
{
  int n;
  cin >> n;

  char G[500][500];
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> G[i][j];
    }
  }

  const int dr[] = {-1, -1, 1, 1};
  const int dc[] = {-1, 1, -1, 1};

  int ans = 0;
  for (int i = 1; i < n-1; i++) {
    for (int j = 1; j < n-1; j++) {
      bool good = G[i][j] == 'X';
      for (int d = 0; d < 4; d++) {
	good &= G[i+dr[d]][j+dc[d]] == 'X';
      }
      ans += good;
    }
  }

  cout << ans << endl;
  return 0;
}
