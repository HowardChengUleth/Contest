#include <bits/stdc++.h>

using namespace std;

int grid[1001][1001];

int main()
{
  string line;
  while (getline(cin, line)) {
    replace(begin(line), end(line), '-', ' ');
    replace(begin(line), end(line), '>', ' ');
    replace(begin(line), end(line), ',', ' ');
    istringstream iss(line);

    int x1, y1, x2, y2;
    iss >> x1 >> y1 >> x2 >> y2;

    assert(0 <= x1 && x1 <= 1000 &&
	   0 <= x2 && x2 <= 1000 &&
	   0 <= y1 && y1 <= 1000 &&
	   0 <= y2 && y2 <= 1000);
    
    if (x1 == x2) {
      for (int y = min(y1, y2); y <= max(y1, y2); y++) {
	grid[y][x1]++;
      }
    } else if (y1 == y2) {
      for (int x = min(x1, x2); x <= max(x1, x2); x++) {
	grid[y1][x]++;
      }
    } else {
      int dx = (x2 - x1) / abs(x2 - x1);
      int dy = (y2 - y1) / abs(y2 - y1);
      for (int x = x1, y = y1; x != x2+dx && y != y2+dy; x += dx, y += dy) {
	grid[y][x]++;
      }
    }
  }

  int ans = 0;
  for (int x = 0; x <= 1000; x++) {
    for (int y = 0; y <= 1000; y++) {
      if (grid[x][y] >= 2) {
	ans++;
      }
    }
  }

  cout << ans << endl;

  return 0;
}
