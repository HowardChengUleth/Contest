#include <bits/stdc++.h>

using namespace std;

const int dr[] = { -1, 0, 1, 0 };
const int dc[] = { 0, 1, 0, -1 };
const string dirchar = "^>v<";

int gr, gc, gdir;
int M, N;

vector<string> read_grid()
{
  vector<string> grid;
  string line;

  int r = 0;
  while (getline(cin, line)) {
    grid.push_back(line);
    for (int c = 0; c < line.length(); c++) {
      if (dirchar.find(line[c]) != string::npos) {
	gr = r;
	gc = c;
	gdir = dirchar.find(line[c]);
      }
    }
    r++;
  }
  M = grid.size();
  N = grid[0].size();

  return grid;
}

bool inside(int r, int c)
{
  return 0 <= r && r < M && 0 <= c && c < N;
}

bool stuck(const vector<string> &grid, int gr, int gc, int gdir)
{
  bool visited[200][200][4] = {false};

  while (inside(gr, gc)) {
    if (visited[gr][gc][gdir]) {
      return true;
    }
    visited[gr][gc][gdir] = true;

    int next_r = gr + dr[gdir], next_c = gc + dc[gdir];
    if (inside(next_r, next_c) && grid[next_r][next_c] == '#') {
      gdir = (gdir + 1) % 4;
    } else {
      gr = next_r;
      gc = next_c;
    }
  }
  
  return false;
}

int main()
{
  auto orig_grid = read_grid();
  auto grid = orig_grid;
  int orig_gr = gr, orig_gc = gc, orig_gdir = gdir;

  // mark the grid as in part (a)
  while (inside(gr, gc)) {
    if (grid[gr][gc] != 'X') {
      grid[gr][gc] = 'X';
    }

    int next_r = gr + dr[gdir], next_c = gc + dc[gdir];
    if (inside(next_r, next_c) && grid[next_r][next_c] == '#') {
      gdir = (gdir + 1) % 4;
    } else {
      gr = next_r;
      gc = next_c;
    }
  }

  int ans = 0;
  for (int r = 0; r < M; r++) {
    for (int c = 0; c < N; c++) {
      if (r == orig_gr && c == orig_gc) continue;
      if (grid[r][c] != 'X') continue;
      orig_grid[r][c] = '#';
      if (stuck(orig_grid, orig_gr, orig_gc, orig_gdir)) {
	ans++;
      }
      orig_grid[r][c] = '.';
    }
  }

  cout << ans << endl;
  
  return 0;
}
