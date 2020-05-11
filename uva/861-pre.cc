#include <iostream>
#include <cstdlib>

using namespace std;

struct Cell
{
  int row, col;

  Cell(int r = 0, int c = 0) : row(r), col(c) { }
  
  bool conflict(const Cell &c)
  {
    return abs(row - c.row) == abs(col - c.col);
  }
};

long long search(Cell subset[], int n, int k, int chosen = 0, 
		 int r = 0, int c = 0)
{
  if (chosen == k) {
    return 1;
  }

  if (c >= n) {
    r++;
    c = 0;
  }

  if (n*n - (r*n + c) + chosen < k) {
    return 0;
  }

  // try not choosing it
  long long ans = search(subset, n, k, chosen, r, c+1);

  // try choosing it
  bool good = true;
  Cell curr(r, c);

  for (int i = 0; i < chosen && good; i++) {
    good &= !curr.conflict(subset[i]);
  }

  if (good) {
    subset[chosen] = curr;
    ans += search(subset, n, k, chosen+1, r, c+1);
  }
  return ans;
}

int main(void)
{
  Cell subset[64];

  cout << "long long ans[9][65] = {" << endl;
  cout << "  {";
  for (int k = 0; k <= 64; k++) {
    if (k) cout << ",";
    cout << "0";
  }
  cout << "}," << endl;

  for (int n = 1; n <= 8; n++) {
    cout << "  {";
    for (int k = 0; k <= 64; k++) {
      long long ans = 0;
      if (k <= n*n) {
	ans = search(subset, n, k);
      }
      if (k) cout << ",";
      cout << ans << "LL";
    }
    cout << "}," << endl;
  }
  cout << "};";
  
  return 0;
}
