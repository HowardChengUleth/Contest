#include <iostream>
#include <algorithm>

using namespace std;

void solve()
{
  int A[1025][1025];

  for (int i = 0; i < 1025; i++) {
    fill(A[i], A[i]+1025, 0);
  }

  int d, n;
  cin >> d >> n;
  for (int i = 0; i < n; i++) {
    int x, y, p;
    cin >> x >> y >>p;
    A[x][y] = p;
  }

  for (int j = 1; j < 1025; j++) {
    A[0][j] += A[0][j-1];
  }
  
  for (int i = 1; i < 1025; i++) {
    A[i][0] += A[i-1][0];
    for (int j = 1; j < 1025; j++) {
      A[i][j] += A[i-1][j] + A[i][j-1] - A[i-1][j-1];
    }
  }

  int bestx, besty, best_sum = -1;

  for (int x = 0; x < 1025; x++) {
    for (int y = 0; y < 1025; y++) {
      int minx = max(x - d, 0), maxx = min(x + d, 1024);
      int miny = max(y - d, 0), maxy = min(y + d, 1024);

      int temp = A[maxx][maxy];
      if (minx > 0) {
	temp -= A[minx-1][maxy];
      }
      if (miny > 0) {
	temp -= A[maxx][miny-1];
      }
      if (minx > 0 && miny > 0) {
	temp += A[minx-1][miny-1];
      }
      if (temp > best_sum) {
	best_sum = temp;
	bestx = x;
	besty = y;
      }
    }
  }

  cout << bestx << ' ' << besty << ' ' << best_sum << endl;
}
	  
int main()
{
  int n;
  cin >> n;
  while (n--)
    solve();

  return 0;
}
