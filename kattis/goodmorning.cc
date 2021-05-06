#include <bits/stdc++.h>

using namespace std;

const int row[10] = { 3, 0, 0, 0, 1, 1, 1, 2, 2, 2 };
const int col[10] = { 1, 0, 1, 2, 0, 1, 2, 0, 1, 2 };

bool valid(int k)
{
  if (k < 0) return false;
  if (k == 0) return true;

  int curr_r = 4, curr_c = 4;
  while (k > 0) {
    int d = k % 10;
    k /= 10;

    if (!(row[d] <= curr_r && col[d] <= curr_c))
      return false;

    curr_r = row[d];
    curr_c = col[d];
  }

  return true;
}

void solve()
{
  int k;
  cin >> k;

  for (int d = 0; ; d++) {
    if (valid(k+d)) {
      cout << k+d << endl;
      return;
    }
    if (valid(k-d)) {
      cout << k-d << endl;
      return;
    }
  }
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
