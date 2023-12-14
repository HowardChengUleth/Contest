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

void rollN(int c)
{
  int to = 0;
  for (int r = 0; r < M; r++) {
    if (grid[r][c] == '.') continue;
    if (grid[r][c] == '#') {
      to = r+1;
    } else {
      grid[r][c] = '.';
      while (grid[to][c] == '#')
	to++;
      grid[to++][c] = 'O';
    }
  }
}

void rollS(int c)
{
  int to = M-1;
  for (int r = M-1; r >= 0; r--) {
    if (grid[r][c] == '.') continue;
    if (grid[r][c] == '#') {
      to = r-1;
    } else {
      grid[r][c] = '.';
      while (grid[to][c] == '#')
	to--;
      grid[to--][c] = 'O';
    }
  }
}

void rollW(int r)
{
  int to = 0;
  for (int c = 0; c < N; c++) {
    if (grid[r][c] == '.') continue;
    if (grid[r][c] == '#') {
      to = c+1;
    } else {
      grid[r][c] = '.';
      while (grid[r][to] == '#')
	to++;
      grid[r][to++] = 'O';
    }
  }
}

void rollE(int r)
{
  int to = N-1;
  for (int c = N-1; c >= 0; c--) {
    if (grid[r][c] == '.') continue;
    if (grid[r][c] == '#') {
      to = c-1;
    } else {
      grid[r][c] = '.';
      while (grid[r][to] == '#')
	to--;
      grid[r][to--] = 'O';
    }
  }
}

void cycle()
{
  for (int c = 0; c < N; c++) {
    rollN(c);
  }
  for (int r = 0; r < M; r++) {
    rollW(r);
  }
  for (int c = 0; c < N; c++) {
    rollS(c);
  }
  for (int r = 0; r < M; r++) {
    rollE(r);
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
  map<vector<string>,int> step;
  vector<vector<string>> mem;
  
  step[grid] = 0;
  mem.push_back(grid);
  
  const int cycle_total_steps = 1000000000;
  for (int i = 1; i <= cycle_total_steps; ) {
    cycle();
    if (step.find(grid) == step.end()) {
      mem.push_back(grid);
      step[grid] = i++;
    } else {
      // found cycle
      int cycle_len = i - step[grid];
      i += (cycle_total_steps - i) / cycle_len * cycle_len + 1;
      step.clear();
    }
  }
  
  int ans = compute_load();
  cout << ans << endl;
  return 0;
}
