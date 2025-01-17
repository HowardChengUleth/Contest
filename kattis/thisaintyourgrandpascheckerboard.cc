#include <bits/stdc++.h>

using namespace std;

int mycount(char grid[24][24], int n, int r, int c, int dr, int dc,
	    char match)
{
  int ans = 0;
  for (int i = 0; i < n; i++) {
    if (grid[r][c] == match) {
      ans++;
    }
    r += dr;
    c += dc;
  }
  return ans;
}

bool check3(char grid[24][24], int n, int r, int c, int dr, int dc)
{
  for (int i = 0; i < n-2; i++) {
    if (grid[r][c] == grid[r + dr][c + dc] &&
	grid[r][c] == grid[r + 2*dr][c + 2*dc]) {
      return true;
    }

    r += dr;
    c += dc;
  }

  return false;
}


bool check(char grid[24][24], int n)
{
  for (int r = 0; r < n; r++) {
    int black = mycount(grid, n, r, 0, 0, 1, 'B');
    if (black != n/2) {
      return false;
    }
    if (check3(grid, n, r, 0, 0, 1)) {
      return false;
    }
  }

  for (int c = 0; c < n; c++) {
    int black = mycount(grid, n, 0, c, 1, 0, 'B');
    if (black != n/2) {
      return false;
    }
    if (check3(grid, n, 0, c, 1, 0)) {
      return false;
    }
  }
  
  return true;
}

int main()
{
  int n;
  cin >> n;

  char grid[24][24];
  for (int r = 0; r < n; r++) {
    for (int c = 0; c < n; c++) {
      cin >> grid[r][c];
    }
  }

  cout << check(grid, n) << endl;

  return 0;
}
