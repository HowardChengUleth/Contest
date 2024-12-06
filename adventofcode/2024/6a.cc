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

int main()
{
  auto grid = read_grid();

  int ans = 0;
  while (inside(gr, gc)) {
    if (grid[gr][gc] != 'X') {
      grid[gr][gc] = 'X';
      ans++;
    }

    int next_r = gr + dr[gdir], next_c = gc + dc[gdir];
    if (inside(next_r, next_c) && grid[next_r][next_c] == '#') {
      gdir = (gdir + 1) % 4;
    } else {
      gr = next_r;
      gc = next_c;
    }
  }

  cout << ans << endl;
  return 0;
}
