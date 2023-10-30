#include <bits/stdc++.h>

using namespace std;

int r, c, n;
int grid[500][500];
bool pass[500][500];
int memo[500][501][11];

int f(int i, int j, int n)
{
  if (i < 0 || i >= r) {
    return INT_MAX;
  }
  
  int &ans = memo[i][j][n];
  if (ans != -1) {
    return ans;
  }

  ans = INT_MAX;
  if (grid[i][j] == -1) {
    return ans;
  }
  
  if (j == c-1) {
    return ans = (n == 0) ? grid[i][j] : INT_MAX;
  }

  if (pass[i][j] && n == 0) {
    return INT_MAX;
  }

  for (int i2 = i-1; i2 <= i+1; i2++) {
    int temp = f(i2, j+1, n - pass[i][j]);
    if (temp < INT_MAX) {
      temp += grid[i][j];
    }
    ans = min(ans, temp);
  }

  return ans;
}

int main()
{
  cin >> r >> c >> n;
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      cin >> grid[i][j];
    }
  }

  for (int i = 1; i < r-1; i++) {
    for (int j = 1; j < c-1; j++) {
      if (grid[i][j] == -1 || grid[i][j-1] == -1 || grid[i][j+1] == -1)
	continue;
      pass[i][j] = (grid[i][j-1] < grid[i][j] && grid[i][j+1] < grid[i][j] &&
		    grid[i-1][j] > grid[i][j] && grid[i+1][j] > grid[i][j]);
    }
  }

  for (int i = 0; i < r; i++) {
    for (int j = 0; j <= c; j++) {
      for (int k = 0; k <= n; k++) {
	memo[i][j][k] = -1;
      }
    }
  }

  int ans = INT_MAX;
  for (int i = 0; i < r; i++) {
    ans = min(ans, f(i, 0, n));
  }

  if (ans == INT_MAX) {
    cout << "impossible" << endl;
  } else {
    cout << ans << endl;
  }
  
  return 0;
}
