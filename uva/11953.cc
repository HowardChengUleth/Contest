#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>

using namespace std;

char grid[100][100];
int n;

void dfs(int r, int c)
{
  grid[r][c] = '.';
  if (r > 0 && grid[r-1][c] != '.') {
    dfs(r-1, c);
  }
  if (r < n-1 && grid[r+1][c] != '.') {
    dfs(r+1, c);
  }
  if (c > 0 && grid[r][c-1] != '.') {
    dfs(r, c-1);
  }
  if (c < n-1 && grid[r][c+1] != '.') {
    dfs(r, c+1);
  }
}

void solve()
{
  cin >> n;

  for (int r = 0; r < n; r++) {
    for (int c = 0; c < n; c++) {
      cin >> grid[r][c];
    }
  }

  int count = 0;
  for (int r = 0; r < n; r++) {
    for (int c = 0; c < n; c++) {
      if (grid[r][c] != 'x') continue;
      dfs(r, c);
      count++;
    }
  }

  cout << count << endl;
}

int main(void)
{
  int T;
  cin >> T;
  for (int i = 1; i <= T; i++) {
    cout << "Case " << i << ": ";
    solve();
  }
  return 0;
}
