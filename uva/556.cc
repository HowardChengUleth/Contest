#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

const int dr[] = { -1, 0, 1, 0 };
const int dc[] = {  0, 1, 0, -1 };

int b, w;
vector<string> grid;
vector< vector<int> > times;

void move(int &r, int &c, int &dir)
{
  int nr = r + dr[dir], nc = c + dc[dir];
  if (!(0 <= nr && nr < b && 0 <= nc && nc < w) ||
      grid[nr][nc] != '0') {
    // can't go forward, turn left
    dir = (dir + 3) % 4;
    //    cout << "  turn left" << endl;
    move(r, c, dir);
    return;
  }

  int right = (dir+1) % 4;
  int rightr = nr + dr[right], rightc = nc + dc[right];
  if (!(0 <= rightr && rightr < b && 0 <= rightc && rightc < w) ||
      grid[rightr][rightc] != '0') {
    // can go forward because there is a wall to the right
    r = nr;
    c = nc;
    //    cout << "Move forward to (" << r << ", " << c << ")" << endl;
    times[r][c]++;
    return;
  }

  // must turn right
  //  cout << "Move forward to (" << nr << ", " << nc << ")" << endl;
  times[nr][nc]++;
  r = nr;
  c = nc;
  if (r == b-1 && c == 0) return;

  //  cout << "Turn right to (" << rightr << ", " << rightc << ")" << endl;
  times[rightr][rightc]++;
  r = rightr;
  c = rightc;
  dir = right;
}

bool solve()
{
  cin >> b >> w;
  if (!b && !w) return false;

  grid.resize(b);
  for (int i = 0; i < b; i++) {
    cin >> grid[i];
  }

  times.resize(b);
  for (int i = 0; i < b; i++) {
    times[i].resize(w);
    fill(times[i].begin(), times[i].end(), 0);
  }

  int r = b-1, c = 0, dir = 1;
  do {
    move(r, c, dir);
  } while (!(r == b-1 && c == 0));

  int count[5] = {0};
  for (int i = 0; i < b; i++) {
    for (int j = 0; j < w; j++) {
      if (grid[i][j] == '0') {
	count[times[i][j]]++;
      }
    }
  }
  for (int i = 0; i < 5; i++) {
    cout << setw(3) << count[i];
  }
  cout << endl;
  return true;
}

int main(void)
{
  while (solve())
    ;
  return 0;
}
