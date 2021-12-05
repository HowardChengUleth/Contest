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
	grid[x1][y]++;
      }
    }
    if (y1 == y2) {
      for (int x = min(x1, x2); x <= max(x1, x2); x++) {
	grid[x][y1]++;
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
