#include <bits/stdc++.h>

using namespace std;

vector<string> H;

int main()
{
  string line;
  while (getline(cin, line)) {
    H.push_back(line);
  }

  int m = H.size();
  int n = H[0].size();


  int left[100][100], right[100][100], up[100][100], down[100][100];

  for (int r = 0; r < m; r++) {
    left[r][0] = -1;
    for (int c = 0; c < n-1; c++) {
      left[r][c+1] = max(left[r][c], H[r][c] - '0');
    }
    right[r][n-1] = -1;
    for (int c = n-1; c > 0; c--) {
      right[r][c-1] = max(right[r][c], H[r][c] - '0');
    }
  }

  for (int c = 0; c < n; c++) {
    up[0][c] = -1;
    for (int r = 0; r < m-1; r++) {
      up[r+1][c] = max(up[r][c], H[r][c] - '0');
    }
    down[m-1][c] = -1;
    for (int r = m-1; r > 0; r--) {
      down[r-1][c] = max(down[r][c], H[r][c] - '0');
    }
  }

  int ans = 0;
  for (int r = 0; r < m; r++) {
    for (int c = 0; c < n; c++) {

      int h = H[r][c] - '0';
      if (h > left[r][c] || h > right[r][c] || h > up[r][c] || h > down[r][c]) {
	ans++;
      }
    }

  }
  cout << ans << endl;
  return 0;
}
