#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

int d[40];

// height[i][j] = min height to reach height j after i jumps
// -2 == uninit
// -1 == impossible
int height[41][1001];

// ans[i][j] = string to get there
string ans[41][1001];

int compute(int m, int h)
{
  if (m == 0) {
    if (!h) {
      ans[m][h] = "";
      return height[m][h] = 0;
    } else {
      return height[m][h] = -1;
    }
  }

  if (height[m][h] != -2) return height[m][h];

  int temp = 10000000;

  // jump down to get here
  compute(m-1, h+d[m-1]);
  if (height[m-1][h+d[m-1]] != -1) {
    temp = min(temp, height[m-1][h+d[m-1]]);
    if (temp == height[m-1][h+d[m-1]]) {
      ans[m][h] = ans[m-1][h+d[m-1]] + 'D';
    }
  }

  // jump up to get here
  if (h-d[m-1] >= 0) {
    compute(m-1, h-d[m-1]);
    if (height[m-1][h-d[m-1]] != -1) {
      int t2 = max(height[m-1][h-d[m-1]], h);
      temp = min(temp, t2);
      if (temp == t2) {
	ans[m][h] = ans[m-1][h-d[m-1]] + 'U';
      }
    }
  }
  
  if (temp > 10000) {
    temp = -1;
  }
  return height[m][h] = temp;
}

void solve()
{
  int m;
  cin >> m;

  for (int i = 0; i < m; i++) {
    cin >> d[i];
  }

  for (int i = 0; i <= m; i++) {
    for (int j = 0; j <= 1000; j++) {
      height[i][j] = -2;
      ans[i][j] = "";
    }
  }

  compute(m, 0);
  if (height[m][0] >= 0) {
    cout << ans[m][0] << endl;
  } else {
    cout << "IMPOSSIBLE" << endl;
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
