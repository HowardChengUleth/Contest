#include <bits/stdc++.h>
#include <cassert>

using namespace std;

typedef vector<string> vs;
int M, N;
int robot_r, robot_c;

vs read_grid()
{
  vs A;
  string line;
  while (getline(cin, line) && line != "") {
    A.push_back(line);
  }
  M = A.size();
  N = A[0].length();

  for (int r = 0; r < M; r++) {
    for (int c = 0; c < N; c++) {
      if (A[r][c] == '@') {
	robot_r = r;
	robot_c = c;
      }
    }
  }
  
  return A;
}

void print_grid(const vs &grid)
{
  for (auto s : grid) {
    cout << s << endl;
  }
  cout << endl;
}

const int dr[] = { -1, 1, 0, 0 };
const int dc[] = { 0, 0, -1, 1 };
const string dirstr = "^v<>";
typedef long long ll;

int gps(int r, int c)
{
  return 100*r + c;
}

bool inside(int r, int c)
{
  return 0 <= r && r < M && 0 <= c && c < N;
}

void try_move(vs &grid, int dir)
{
  int r2 = robot_r + dr[dir], c2 = robot_c + dc[dir];

  // don't walk off grid or into wall
  if (!inside(r2, c2) || grid[r2][c2] == '#') return;

  if (grid[r2][c2] == '.') {
    // empty spot, just move
    grid[r2][c2] = '@';
    grid[robot_r][robot_c] = '.';
    robot_r = r2;
    robot_c = c2;
    return;
  }

  assert(grid[r2][c2] == 'O');
  r2 += dr[dir];
  c2 += dc[dir];
  while (inside(r2, c2) && grid[r2][c2] == 'O') {
    r2 += dr[dir];
    c2 += dc[dir];
  }

  // cannot push off grid or into walls
  if (!inside(r2, c2) || grid[r2][c2] == '#') return;

  grid[r2][c2] = 'O';
  grid[robot_r][robot_c] = '.';
  robot_r += dr[dir];
  robot_c += dc[dir];
  grid[robot_r][robot_c] = '@';
}

int main()
{
  vs grid = read_grid();

  char cmd;
  while (cin >> cmd) {
    int dir = dirstr.find(cmd);
    try_move(grid, dir);
  }

  ll ans = 0;
  for (int r = 0; r < M; r++) {
    for (int c = 0; c < N; c++) {
      if (grid[r][c] != 'O') continue;
      ans += gps(r, c);
    }
  }

  cout << ans << endl;

  return 0;
}
