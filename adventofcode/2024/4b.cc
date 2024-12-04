#include <bits/stdc++.h>

using namespace std;

const int dr[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
const int dc[] = { -1, 0, 1, -1, 1, -1, 0, 1 };

bool search(const vector<string> &grid, int M, int N, int r, int c)
{
  if (grid[r][c] != 'A') return false;
  if (!(0 <= r-1 && 0 <= c-1 && r+1 < M && c+1 < N)) return false;
  string s1 = string(1, grid[r-1][c-1]) + grid[r+1][c+1];
  string s2 = string(1, grid[r-1][c+1]) + grid[r+1][c-1];

  return (s1 == "MS" || s1 == "SM") && (s2 == "MS" || s2 == "SM");
}

int main()
{
  long long ans = 0;

  vector<string> grid;
  string line;
  while (getline(cin, line)) {
    grid.push_back(line);
  }

  int M = grid.size(), N = grid[0].size();
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      if (search(grid, M, N, i, j)) {
	ans++;
      }
    }
  }

  cout << ans << endl;
  
  return 0;
}
