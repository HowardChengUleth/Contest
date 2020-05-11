#include <iostream>
#include <string>

using namespace std;

bool solve()
{
  int n, m, s;
  cin >> n >> m >> s;

  if (!n && !m && !s) return false;

  string grid[100];
  for (int i = 0; i < n; i++) {
    cin >> grid[i];
  }

  const int dr[4] = { -1, 0, 1, 0 };
  const int dc[4] = { 0, -1, 0, 1 };
  int rr, rc, rorient;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (grid[i][j] == 'N') {
	rr = i; rc = j; rorient = 0;
      } else if (grid[i][j] == 'S') {
	rr = i; rc = j; rorient = 2;
      } else if (grid[i][j] == 'L') {
	rr = i; rc = j; rorient = 3;
      } else if (grid[i][j] == 'O') {
	rr = i; rc = j; rorient = 1;
      }
    }
  }

  string cmd;
  cin >> cmd;
  int count = 0;

  for (int i = 0; i < cmd.length(); i++) {
    if (cmd[i] == 'D') {
      rorient = (rorient + 3) % 4;
    } else if (cmd[i] == 'E') {
      rorient = (rorient + 1) % 4;
    } else if (cmd[i] == 'F') {
      int nr = rr + dr[rorient];
      int nc = rc + dc[rorient];
      if (0 <= nr && nr < n && 0 <= nc && nc < m &&
	  grid[nr][nc] != '#') {
	if (grid[nr][nc] == '*') {
	  count++;
	  grid[nr][nc] = '.';
	}
	rr = nr;
	rc = nc;
      } else {
      }
    }
  }
  cout << count << endl;
  
  return true;
}

int main(void)
{
  while (solve())
    ;
  return 0;
}
