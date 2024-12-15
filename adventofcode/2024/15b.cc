#include <bits/stdc++.h>
#include <cassert>

using namespace std;

typedef vector<string> vs;
int M, N;
int robot_r, robot_c;

vs read_grid()
{
  map<char, string> rep;
  rep['#'] = "##";
  rep['O'] = "[]";
  rep['.'] = "..";
  rep['@'] = "@.";
  
  vs A;
  string line;
  while (getline(cin, line) && line != "") {
    string Aline;
    for (auto ch : line) {
      Aline += rep[ch];
    }
    A.push_back(Aline);
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

void move_LR(vs &grid, int dir)
{
  int r = robot_r;
  int c = robot_c + dc[dir];

  // we know we are pushing into a box
  int c2 = c + dc[dir];
  while (inside(r, c2) && (grid[r][c2] == '[' || grid[r][c2] == ']')) {
    c2 += dc[dir];
  }

  // cannot push off grid or into walls
  if (!inside(r, c2) || grid[r][c2] == '#') return;

  // now shift everything
  for (int c3 = c2; c3 != robot_c; c3 -= dc[dir]) {
    grid[r][c3] = grid[r][c3-dc[dir]];
  }
  grid[robot_r][robot_c] = '.';
  robot_c += dc[dir];
}

bool check_move_UD(const vs &grid, int r, int c, int dir)
{
  int r2 = r + dr[dir];
  int c2 = c;

  // don't push outside or 
  if (!inside(r2, c2) || grid[r2][c2] == '#')
    return false;

  // we can push
  if (grid[r2][c2] == '.')
    return true;

  if (grid[r2][c2] == '[') {
    return check_move_UD(grid, r2, c2, dir) &&
      check_move_UD(grid, r2, c2+1, dir);
  }

  if (grid[r2][c2] == ']') {
    return check_move_UD(grid, r2, c2-1, dir) &&
      check_move_UD(grid, r2, c2, dir);
  }

  cout << "r, c = " << r << ' ' << c << endl;
  cout << "r2, c2 = " << r2 << ' ' << c2 << endl;
  assert(false);
  
  return false;
}

void move_UD(vs &grid, int r, int c, int dir)
{
  int r2 = r + dr[dir];
  int c2 = c;

  // we know we can move
  if (grid[r2][c2] == '[') {
    move_UD(grid, r2, c2, dir);
    move_UD(grid, r2, c2+1, dir);
  } else if (grid[r2][c2] == ']') {
    move_UD(grid, r2, c2-1, dir);
    move_UD(grid, r2, c2, dir);
  }

  // we know we can move
  assert(grid[r2][c2] == '.');
  grid[r2][c2] = grid[r][c];
  grid[r][c] = '.';
  if (grid[r2][c2] == '@') {
    robot_r = r2;
    robot_c = c2;
  }
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

  if (dir < 2) {
    // move up or down
    if (check_move_UD(grid, robot_r, robot_c, dir)) {
      move_UD(grid, robot_r, robot_c, dir);
    }
  } else {
    // move left or right
    move_LR(grid, dir);
  }

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
      if (grid[r][c] != '[') continue;
      ans += gps(r, c);
    }
  }

  cout << ans << endl;

  return 0;
}
