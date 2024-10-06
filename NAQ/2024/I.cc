#include <bits/stdc++.h>

using namespace std;

// just check everything they say...

int n;
string grid[30];

bool inside(int r, int c)
{
  return 0 <= r && r < n && 0 <= c && c < n;
}

const int dr[] = { -1, 1, 0, 0 };
const int dc[] = { 0, 0, -1, 1 };

bool all_lit()
{
  bool lit[30][30] = { false };
  for (int r = 0; r < n; r++) {
    for (int c = 0; c < n; c++) {
      if (grid[r][c] != '?') continue;

      for (int d = 0; d < 4; d++) {
	int r2 = r + dr[d], c2 = c + dc[d];

	// light up as long as we are inside and open
	while (inside(r2, c2) && grid[r2][c2] == '.') {
	  lit[r2][c2] = true;
	  r2 += dr[d];
	  c2 += dc[d];
	}

	// did we get stopped by another light?
	if (inside(r2, c2) && grid[r2][c2] == '?') {
	  return false;
	}
      }
    }
  }

  // make sure all open squares are lit
  for (int r = 0; r < n; r++) {
    for (int c = 0; c < n; c++) {
      if (grid[r][c] == '.' && !lit[r][c]) {
	return false;
      }
    }
  }

  return true;
  
}

bool check_adj()
{
  for (int r = 0; r < n; r++) {
    for (int c = 0; c < n; c++) {
      if (!isdigit(grid[r][c])) continue;

      int count = 0;
      for (int d = 0; d < 4; d++) {
	int r2 = r + dr[d], c2 = c + dc[d];
	if (inside(r2, c2) && grid[r2][c2] == '?') {
	  count++;
	}
      }
      if (grid[r][c] - '0' != count) {
	return false;
      }
    }
  }

  return true;
}

int main()
{
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> grid[i];
  }

  bool good = all_lit() && check_adj();
  cout << (good ? 1 : 0) << endl;
    
  
  return 0;
}
