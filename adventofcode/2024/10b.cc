#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

int M, N;

vvi read_input()
{
  vvi grid;

  string line;
  while (getline(cin, line)) {
    vi row;
    for (auto ch : line) {
      row.push_back(ch - '0');
    }
    grid.push_back(row);
  }

  M = grid.size();
  N = grid[0].size();
  
  return grid;
}

const int dr[] = {-1, 1, 0, 0};
const int dc[] = {0, 0, -1, 1};

bool inside(int r, int c)
{
  return 0 <= r && r < M && 0 <= c && c < N;
}


int DP(const vvi&grid, int r, int c, vvi &num_paths)
{
  if (num_paths[r][c] >= 0) {
    return num_paths[r][c];
  }

  int curr_h = grid[r][c];

  if (curr_h == 9) {
    return num_paths[r][c] = 1;
  }
  
  num_paths[r][c] = 0;
  for (int d = 0; d < 4; d++) {
    int r2 = r + dr[d], c2 = c + dc[d];
    if (inside(r2, c2) && grid[r2][c2] == curr_h+1) {
      num_paths[r][c] += DP(grid, r2, c2, num_paths);
    }
  }

  return num_paths[r][c];
}

int main()
{
  int ans = 0;
  vvi grid = read_input();

  vvi num_paths(M, vi(N, -1));

  for (int r = 0; r < M; r++) {
    for (int c = 0; c < N; c++) {
      if (grid[r][c] == 0) {
	ans += DP(grid, r, c, num_paths);
      }
    }
  }
  
  cout << ans << endl;

  return 0;
}
