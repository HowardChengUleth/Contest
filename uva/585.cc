#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

bool solve(int id)
{
  int n;
  cin >> n;
  if (!n) return false;

  string grid[100];
  for (int i = 0; i < n; i++) {
    cin >> grid[i];
  }

  int best[100][100] = {0};

  int H = 0;
  
  // down triangles
  int cols = 2*n-1;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < cols; j += 2) {
      if (grid[i][j] == '#') {
	best[i][j] = 0;
	continue;
      }

      best[i][j] = 1;
      if (i > 0) {
	if (grid[i-1][j+1] == '-') {
	  best[i][j] += min(best[i-1][j], best[i-1][j+2]);
	}
      }

      H = max(best[i][j], H);
    }
    cols -= 2;
  }

  // up triangles
  cols = 1;
  for (int i = n-1; i >= 0; i--) {
    for (int j = 1; j < cols; j+=2) {
      if (grid[i][j] == '#') {
	best[i][j] = 0;
	continue;
      }
      best[i][j] = 1;
      if (i < n-1) {
	int lo = j-2, hi = j;
	if (lo >= 0 && hi < cols-2 && grid[i+1][lo+1] == '-') {
	  best[i][j] += min(best[i+1][lo], best[i+1][hi]);
	}
      }

      H = max(best[i][j], H);
    }
    cols += 2;
  }

  
  int ans = 0;
  cols = 1;
  for (int i = 0; i < H; i++) {
    ans += cols;
    cols += 2;
  }
  cout << "Triangle #" << id << endl;
  cout << "The largest triangle area is " << ans << "." << endl << endl;
  
  return true;
}

int main()
{
  int id = 1;
  while (solve(id++))
    ;

  return 0;
}
