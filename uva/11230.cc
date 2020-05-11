#include <iostream>
#include <algorithm>

using namespace std;

int main(void)
{
  int n, m, r, c;

  while (cin >> n >> m >> r >> c && (n || m || r || c)) {
    char board[100][100];
    char working[100][100];
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
	cin >> board[i][j];
	board[i][j] = (board[i][j] == '1');
      }
      fill(working[i], working[i]+m, 0);
    }

    int count = 0;
    for (int i = 0; i <= n-r; i++) {
      for (int j = 0; j <= m-c; j++) {
	if (working[i][j] == board[i][j]) continue;
	for (int ii = i; ii < i+r; ii++) {
	  for (int jj = j; jj < j+c; jj++) {
	    working[ii][jj] = !working[ii][jj];
	  }
	}
	count++;
      }
    }

    bool good = true;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
	good &= (board[i][j] == working[i][j]);
      }
    }
    if (!good) {
      count = -1;
    }
    cout << count << endl;
  }
  return 0;
}
