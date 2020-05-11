#include <iostream>
#include <algorithm>

using namespace std;

bool solve(bool first)
{
  int t, w, n;
  if (!(cin >> t >> w >> n)) return false;

  if (!first) cout << endl;

  int d[30], v[30];
  for (int i = 0; i < n; i++) {
    cin >> d[n-1-i] >> v[n-1-i];
    d[n-1-i] *= 3*w;
  }

  int profit[31][1001];
  int num[31][1001];
  int prev[31][1001];
  fill(profit[0], profit[0] + t+1, -1);
  profit[0][0] = 0;
  num[0][0] = 0;
  prev[0][0] = 0;

  for (int i = 1; i <= n; i++) {
    fill(profit[i], profit[i] + t + 1, -1);

    for (int j = 0; j <= t; j++) {
      if (profit[i-1][j] < 0) continue;

      if (profit[i-1][j] > profit[i][j]) {
	profit[i][j] = profit[i-1][j];
	num[i][j] = num[i-1][j];
	prev[i][j] = j;
      }

      int newt = j + d[i-1];
      if (newt > t) continue;
      int newp = profit[i-1][j] + v[i-1];
      if (newp > profit[i][newt]) {
	profit[i][newt] = newp;
	num[i][newt] = num[i-1][j] + 1;
	prev[i][newt] = j;
      }
    }
  }

  int maxprofit = 0;
  int maxt = -1;
  for (int j = 0; j <= t; j++) {
    if (profit[n][j] > maxprofit) {
      maxprofit = profit[n][j];
      maxt = j;
    }
  }
  cout << maxprofit << endl;
  cout << num[n][maxt] << endl;

  for (int i = n; i >= 0; i--) {
    int prevt = prev[i][maxt];
    if (prevt != maxt) {
      cout << d[i-1]/(3*w) << ' ' << v[i-1] << endl;
      maxt = prevt;
    } 
  }
  
  return true;
}

int main()
{
  bool first = true;
  while (solve(first)) {
    first = false;
  }
  return 0;
}
