#include <bits/stdc++.h>

using namespace std;

const int ROWS = 800, COLS = 2000;
char grid[ROWS][COLS];

const int SAND_R = 0, SAND_C = 500;
int max_r = 0;

void process(string line)
{
  replace(begin(line), end(line), ',', ' ');
  replace(begin(line), end(line), '-', ' ');
  replace(begin(line), end(line), '>', ' ');
  
  istringstream iss(line);
  int prev_r = -1, prev_c = -1;
  int r, c;
  while (iss >> c >> r) {
    assert(0 <= c && c < COLS && 0 <= r && r < ROWS);
    max_r = max(max_r, r+2);
    if (prev_r != -1) {
      int r1 = min(prev_r, r), r2 = max(prev_r, r);
      int c1 = min(prev_c, c), c2 = max(prev_c, c);
      for (int rr = r1; rr <= r2; rr++) {
	for (int cc = c1; cc <= c2; cc++) {
	  grid[rr][cc] = '#';
	}
      }
    }
    prev_r = r;
    prev_c = c;
  }
  assert(max_r < ROWS);
}

bool drop()
{
  int sr = SAND_R, sc = SAND_C;

  while (sr+1 < ROWS) {
    if (grid[sr+1][sc] == '.') {
      sr++;
    } else if (grid[sr+1][sc-1] == '.') {
      sr++;
      sc--;
      assert(sc >= 0);
    } else if (grid[sr+1][sc+1] == '.') {
      sr++;
      sc++;
      assert(sc < COLS);
    } else {
      grid[sr][sc] = 'o';
      return sr > 0;
    }
  }
  assert(false);
}

int main()
{
  for (int r = 0; r < ROWS; r++) {
    for (int c = 0; c < COLS; c++) {
      grid[r][c] = '.';
    }
  }

  string line;
  while (getline(cin, line)) {
    process(line);
  }

  for (int c = 0; c < COLS; c++) {
    grid[max_r][c] = '#';
  }
  
  int ans = 1;
  while (drop()) {
    ans++;
  }
  for (int r = 0; r < 11; r++) {
    for (int c = 480; c <= 520; c++) {
      cout << grid[r][c];
    }
    cout << endl;
  }
  cout << "-------------" << endl;

  cout << ans << endl;
  cout << "===============" << endl;
  return 0;
}
