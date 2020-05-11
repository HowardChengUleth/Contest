// Idea: relatively straightforward for second rule.  For first rule,
// you can use DFS to collect all the digits in each polynomino and check
// that each digit appears exactly once.
#include <iostream>
#include <algorithm>
#include <cassert>

using namespace std;

int R, C;
int board[15][15];
int descr[15][15];

int DFS(int r, int c, bool mark[15][15], bool used[])
{
  const int dr[] = { -1, 0, 1, 0 };
  const int dc[] = { 0, 1, 0, -1 };

  mark[r][c] = true;
  used[board[r][c]] = true;

  int size = 1;
  
  for (int d = 0; d < 4; d++) {
    int mask = (1 << d);
    if (!(descr[r][c] & mask)) continue;
    int r2 = r + dr[d], c2 = c + dc[d];
    if (0 <= r2 && r2 < R && 0 <= c2 && c2 < C && !mark[r2][c2]) {
      size += DFS(r2, c2, mark, used);
    }
  }
  return size;
}

void solve()
{
  cin >> R >> C;

  for (int r = 0; r < R; r++) {
    for (int c = 0; c < C; c++) {
      char ch;
      cin >> ch;
      board[r][c] = ch - '0';
      assert(1 <= board[r][c] && board[r][c] <= 8);
    }
  }

  for (int r = 0; r < R; r++) {
    for (int c = 0; c < C; c++) {
      cin >> descr[r][c];
    }
  }

  // check row and column distances
  for (int r = 0; r < R; r++) {
    for (int c = 0; c < C; c++) {
      int d = board[r][c];
      for (int k = 1; k <= d; k++) {
	if (r+k < R && board[r+k][c] == d) {
	  goto bad;
	}
	if (c+k < C && board[r][c+k] == d) {
	  goto bad;
	}
      }
    }
  }

  // now check each polyomino
  bool mark[15][15];
  for (int r = 0; r < R; r++) {
    fill(mark[r], mark[r]+C, false);
  }
  for (int r = 0; r < R; r++) {
    for (int c = 0; c < C; c++) {
      if (mark[r][c]) continue;
      bool used[9] = {false};
      int size = DFS(r, c, mark, used);
      for (int i = 1; i <= size; i++) {
	if (!used[i]) {
	  goto bad;
	}
      }
    }
  }
  
  cout << "valid" << endl;
  return;
  
 bad:
  cout << "invalid" << endl;
}

int main()
{
  int T;
  cin >> T;
  while (T--) {
    solve();
  }
  
  return 0;
}
