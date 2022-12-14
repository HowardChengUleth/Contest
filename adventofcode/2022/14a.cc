#include <bits/stdc++.h>

using namespace std;

const int ROWS = 800, COLS = 2000;
char grid[ROWS][COLS];

const int SAND_R = 0, SAND_C = 500;

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
    } else if (grid[sr+1][sc+1] == '.') {
      sr++;
      sc++;
    } else {
      grid[sr][sc] = 'o';
      return true;
    }
  }
  return false;
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

  int ans = 0;
  while (drop()) {
    /*
    for (int r = 0; r < 10; r++) {
      for (int c = 493; c <= 504; c++) {
	cout << grid[r][c];
      }
      cout << endl;
    }
    cout << "-------------" << endl;
    */
    ans++;
  }

  cout << ans << endl;
  cout << "===============" << endl;
  return 0;
}
