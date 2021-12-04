#include <bits/stdc++.h>

using namespace std;

int grid[1002][1002];

int main()
{
  int R, C;
  cin >> R >> C;

  int N;
  cin >> N;
  for (int i = 0; i < N; i++) {
    int r, c;
    cin >> r >> c;
    grid[r][c] = 1;
  }

  int freq[9] = {0};
  for (int r = 1; r <= R; r++) {
    for (int c = 1; c <= C; c++) {
      if (!grid[r][c]) continue;
      int count = -1;
      for (int i = r-1; i <= r+1; i++) {
	for (int j = c-1; j <= c+1; j++) {
	  count += grid[i][j];
	}
      }
      freq[count]++;
    }
  }

  for (int i = 0; i <= 8; i++) {
    cout << freq[i] << ' ';
  }
  cout << endl;
  return 0;
}
