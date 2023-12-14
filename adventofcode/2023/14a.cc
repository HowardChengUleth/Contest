#include <bits/stdc++.h>

using namespace std;

vector<string> grid;
int M, N;

void read_grid()
{
  string line;
  while (getline(cin, line)) {
    grid.push_back(line);
  }
  M = grid.size();
  N = grid[0].size();
}

void shift_column(int c)
{
  int to = 0;
  while (to < M && grid[to][c] == '#')
    to++;
  
  for (int r = 0; r < M; r++) {
    if (grid[r][c] == '.') continue;
    if (grid[r][c] == '#') {
      to = r+1;
    } else {
      assert(to < M);
      grid[r][c] = '.';
      grid[to++][c] = 'O';
      while (to < M && grid[to][c] == '#')
	to++;
    }
  }
}

int compute_load()
{
  int ans = 0;
  for (int r = 0; r < M; r++) {
    for (int c = 0; c < N; c++) {
      if (grid[r][c] == 'O') {
	ans += M - r;
      }
    }
  }
  return ans;
}

int main()
{
  read_grid();
  for (int c = 0; c < N; c++) {
    shift_column(c);
  }
  int ans = compute_load();
  cout << ans << endl;
  return 0;
}
