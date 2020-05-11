#include <iostream>
#include <string>
#include <cassert>

using namespace std;

void solve_case(void)
{
  int R, C;
  cin >> R >> C;
  cin.ignore(1);

  string maze[60];
  for (int i = 0; i < R; i++) {
    getline(cin, maze[i]);
  }

  int dr[4] = { -1, 0, 1, 0 };
  int dc[4] = { 0, 1, 0, -1 };
  string dirname = "NESW";
  int r, c, nr, nc;
  cin >> r >> c;
  r--; c--;
  int dir = 0;
  char ch;
  while (cin >> ch && ch != 'Q') {
    switch(ch) {
    case 'R':
      dir = (dir + 1) % 4;
      break;
    case 'L':
      dir = (dir + 3) % 4;
      break;
    case 'F':
      nr = r + dr[dir];
      nc = c + dc[dir];
      if (0 <= nr && nr < R && 0 <= nc && nc < C && maze[nr][nc] != '*') {
	r = nr;
	c = nc;
      }
      break;
    default:
      assert(0);
    }
  }
  cout << r+1 << ' ' << c+1 << ' ' << dirname[dir] << endl;
}

int main(void)
{
  int C;
  cin >> C;
  while (C-- > 0) {
    solve_case();
    if (C) {
      cout << endl;
    }
  }
  return 0;
}
