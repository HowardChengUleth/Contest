#include <bits/stdc++.h>

using namespace std;

int n, m;
char grid[100][100];
char soln[100][100];
int prefix_treasure[100][100];

char label(int index)
{
  if (index < 26) {
    return 'A' + index;
  } else {
    return 'a' + index - 26;
  }
}

int num_treasure(int r, int c, int s)
{
  int r2 = r+s-1, c2 = c+s-1;
  int ans = prefix_treasure[r2][c2];
  if (r-1 >= 0) {
    ans -= prefix_treasure[r-1][c2];
  }
  if (c-1 >= 0) {
    ans -= prefix_treasure[r2][c-1];
  }
  if (r-1 >= 0 && c-1 >= 0) {
    ans += prefix_treasure[r-1][c-1];
  }

  return ans;
}

bool solve(int r, int c, int curr)
{
  if (r >= n) {
    return true;
  }
  if (c >= m) {
    return solve(r+1, 0, curr);
  }
  if (grid[r][c] == '#') {
    soln[r][c] = '#';
    return solve(r, c+1, curr);
  }
  if (soln[r][c] != 0) {
    return solve(r, c+1, curr);
  }

  for (int s = 1; r+s-1 < n && c+s-1 < m; s++) {
    int t = num_treasure(r, c, s);
    if (t == 0) continue;
    if (t > 1) break;

    int r2 = r+s-1, c2 = c+s-1;
    bool empty = true;
    for (int r1 = r; r1 <= r2; r1++) {
      for (int c1 = c; c1 <= c2; c1++) {
	empty &= (soln[r1][c1] == 0 && grid[r1][c1] != '#');
      }
    }
    if (!empty) continue;
    
    for (int r1 = r; r1 <= r2; r1++) {
      for (int c1 = c; c1 <= c2; c1++) {
	soln[r1][c1] = label(curr);
      }
    }

    if (solve(r, c+1, curr+1)) {
      return true;
    }
    
    for (int r1 = r; r1 <= r2; r1++) {
      for (int c1 = c; c1 <= c2; c1++) {
	soln[r1][c1] = 0;
      }
    }
  }
  
  return false;
}

int main()
{
  cin >> n >> m;
  for (int r = 0; r < n; r++) {
    for (int c = 0; c < m; c++) {
      cin >> grid[r][c];

      prefix_treasure[r][c] = (grid[r][c] == '$' ? 1 : 0);
      if (r-1 >= 0) {
	prefix_treasure[r][c] += prefix_treasure[r-1][c];
      }
      if (c-1 >= 0) {
	prefix_treasure[r][c] += prefix_treasure[r][c-1];
      }
      if (r-1 >= 0 && c-1 >= 0) {
	prefix_treasure[r][c] -= prefix_treasure[r-1][c-1];
      }
    }
  }

  if (solve(0, 0, 0)) {
    for (int r = 0; r < n; r++) {
      for (int c = 0; c < m; c++) {
	cout << soln[r][c];
      }
      cout << endl;
    }
  } else {
    cout << "elgnatcer" << endl;
  }

  return 0;
}
