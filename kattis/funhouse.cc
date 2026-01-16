#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

enum Dir { UP, RIGHT, DOWN, LEFT };   // clockwise from UP
const int dr[] = {-1, 0, 1, 0};
const int dc[] = {0, 1, 0, -1};

bool solve(int C)
{
  int W, L;
  cin >> W >> L;
  if (!W && !L) return false;

  cout << "HOUSE " << C << endl;

  string grid[20];
  for (int i = 0; i < L; i++) {
    cin >> grid[i];
  }


  // find entrance
  int e_r, e_c, e_dir;
  for (int i = 0; i < L; i++) {
    string::size_type p = grid[i].find('*');
    if (p == string::npos) continue;
    e_r = i;
    e_c = p;
    if (e_r == 0) e_dir = DOWN;
    else if (e_r == L-1) e_dir = UP;
    else if (e_c == 0) e_dir = RIGHT;
    else e_dir = LEFT;
  }

  // now trace it
  bool done = false;
  while (!done) {
    e_r += dr[e_dir];
    e_c += dc[e_dir];

    switch (grid[e_r][e_c]) {
    case '/':
      if (e_dir == UP || e_dir == DOWN) {
	e_dir = (e_dir + 1) % 4;
      } else {
	e_dir = (e_dir + 3) % 4;
      }
      break;
    case '\\':
      if (e_dir == UP || e_dir == DOWN) {
	e_dir = (e_dir + 3) % 4;
      } else {
	e_dir = (e_dir + 1) % 4;
      }
      break;
    case 'x':
      done = true;
      grid[e_r][e_c] = '&';
    }
  }

  for (int i = 0; i < L; i++) {
    cout << grid[i] << endl;
  }
  

  return true;
}

int main()
{
  int num = 1;

  while (solve(num++))
    ;

  return 0;
}
