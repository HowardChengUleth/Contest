#include <iostream>
#include <string>

using namespace std;

void solve()
{
  int n;
  string board[100];
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> board[i];
  }

  const int mod = 1000007;
  int ways[100][100];
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (i == 0) {
	ways[i][j] = (board[i][j] != 'B') ? 1 : 0;
      } else {
	ways[i][j] = 0;
	if (j-1 >= 0 && board[i-1][j-1] == '.') {
	  ways[i][j] += ways[i-1][j-1];
	}
	if (j+1 < n && board[i-1][j+1] == '.') {
	  ways[i][j] += ways[i-1][j+1];
	}
	if (i-2 >= 0 && j-2 >= 0 && board[i-2][j-2] == '.' &&
	    board[i-1][j-1] == 'B') {
	  ways[i][j] += ways[i-2][j-2];
	}
	if (i-2 >= 0 && j+2 < n && board[i-2][j+2] == '.' &&
	    board[i-1][j+1] == 'B') {
	  ways[i][j] += ways[i-2][j+2];
	}
      }
      ways[i][j] %= mod;
      if (board[i][j] == 'W') {
	cout << ways[i][j] << endl;
	return;
      }
    }
  }
}

int main(void)
{
  int T;
  cin >> T;
  for (int i = 1; i <= T; i++) {
    cout << "Case " << i << ": ";
    solve();
  }
  return 0;
}
