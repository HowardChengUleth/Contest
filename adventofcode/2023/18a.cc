#include <bits/stdc++.h>

using namespace std;

const string dir = "URDL";
const int dr[] = {-1, 0, 1, 0};
const int dc[] = {0, 1, 0, -1};

vector<int> cmd_dir, cmd_step;
vector<string> cmd_color;

bool read_cmd()
{
  char D;
  int s;
  string c;

  if (!(cin >> D >> s >> c))
    return false;

  cmd_dir.push_back(dir.find(D));
  cmd_step.push_back(s);
  cmd_color.push_back(c);

  return true;
}

vector<string> grid;
int M, N;

void trace_grid()
{
  int min_r, max_r, min_c, max_c;
  min_r = max_r = min_c = max_c = 0;
  
  int r = 0, c = 0;
  for (int i = 0; i < (int)cmd_dir.size(); i++) {
    r += dr[cmd_dir[i]] * cmd_step[i];
    c += dc[cmd_dir[i]] * cmd_step[i];

    min_r = min(min_r, r);
    min_c = min(min_c, c);
    max_r = max(max_r, r);
    max_c = max(max_c, c);
  }

  M = max_r - min_r + 1 + 2;
  N = max_c - min_c + 1 + 2;

  grid.resize(M, string(N, '.'));
  r = 0 - (min_r - 1);
  c = 0 - (min_c - 1);

  for (int i = 0; i < (int)cmd_dir.size(); i++) {
    for (int k = 0; k < cmd_step[i]; k++) {
      r += dr[cmd_dir[i]];
      c += dc[cmd_dir[i]];
      grid[r][c] = '#';
    }
  }
}

typedef pair<int,int> pii;

bool inside(int r, int c)
{
  return 0 <= r && r < M && 0 <= c && c < N;
}

void fill_outside()
{
  queue<pii> q;
  q.emplace(0, 0);
  grid[0][0] = 'x';
  while (!q.empty()) {
    auto [r, c] = q.front();
    q.pop();

    for (int d = 0; d < 4; d++) {
      int r2 = r + dr[d];
      int c2 = c + dc[d];
      if (!inside(r2, c2)) continue;
      if (grid[r2][c2] != '.') continue;
      grid[r2][c2] = 'x';
      q.emplace(r2, c2);
    }
  }
  
}

int main()
{
  while (read_cmd())
    ;
  
  trace_grid();
  fill_outside();

  int ans = 0;
  for (auto s : grid) {
    for (auto c : s) {
      if (c != 'x') {
	ans++;
      }
    }
  }
  cout << ans << endl;
  return 0;
}
