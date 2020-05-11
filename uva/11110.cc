#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>

using namespace std;

int grid[100][100];
int n;

int dfs(int r, int c)
{
  int ans = 1;

  int label = grid[r][c];
  grid[r][c] = -1;
  if (r > 0 && grid[r-1][c] == label) {
    ans += dfs(r-1, c);
  }
  if (r < n-1 && grid[r+1][c] == label) {
    ans += dfs(r+1, c);
  }
  if (c > 0 && grid[r][c-1] == label) {
    ans += dfs(r, c-1);
  }
  if (c < n-1 && grid[r][c+1] == label) {
    ans += dfs(r, c+1);
  }
  return ans;
}

int main(void)
{
  while (cin >> n && n) {
    cin.ignore(1);

    for (int i = 0; i < n; i++) {
      fill(grid[i], grid[i]+n, 0);
    }

    bool good = true;
    int count[100] = {0};
    for (int label = 1; label < n; label++) {
      string line;
      getline(cin, line);
      istringstream iss(line);

      int r, c;
      while (iss >> r >> c) {
	good &= (grid[r-1][c-1] == 0 || grid[r-1][c-1] == label);
	if (grid[r-1][c-1] == 0) {
	  count[label]++;
	}
	grid[r-1][c-1] = label;
      }

      good &= (count[label] == n);
    }

    for (int r = 0; r < n && good; r++) {
      for (int c = 0; c < n && good; c++) {
	if (grid[r][c] >= 0 && dfs(r, c) != n) {
	  good = false;
	}
      }
    }
    cout << (good ? "good" : "wrong") << endl;
  }
  return 0;
}
