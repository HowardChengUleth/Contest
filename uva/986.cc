#include <iostream>

using namespace std;

// table[x][y][p][d] = number of ways to get to x, y having already
// had p peaks at height k, and the last move is d (up = 0, down = 1)
long long table[40][40][20][2];

void solve(int n, int r, int k)
{
  for (int x = 0; x <= 2*n; x++) {
    for (int y = 0; y <= 2*n; y++) {
      for (int p = 0; p <= n; p++) {
	for (int d = 0; d <= 1; d++) {
	  table[x][y][p][d] = 0;
	}
      }
    }
  }

  // first step must be up
  table[1][1][0][0] = 1;
  for (int x = 2; x <= 2*n; x++) {
    for (int y = 0; y <= 2*n; y++) {
      // try to move up from previous step
      if (y > 0) {
	for (int p = 0; p <= n; p++) {
	  table[x][y][p][0] += table[x-1][y-1][p][0] + table[x-1][y-1][p][1];
	}
      }
      
      // try to move down from the previous step
      if (y < 2*n) {
	for (int p = 0; p <= n; p++) {
	  table[x][y][p][1] += table[x-1][y+1][p][1];
	  if (y+1 == k) {
	    table[x][y][p+1][1] += table[x-1][y+1][p][0];
	  } else {
	    table[x][y][p][1] += table[x-1][y+1][p][0];
	  }
	}
      }
    }
  }
  cout << table[2*n][0][r][1] << endl;
}

int main(void)
{
  int n, r, k;
  while (cin >> n >> r >> k) {
    solve(n, r, k);
  }

  return 0;
}
