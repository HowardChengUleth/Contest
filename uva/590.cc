#include <iostream>
#include <algorithm>

using namespace std;

bool solve(int id)
{
  int n, k;
  cin >> n >> k;
  if (!n && !k) return false;
  cout << "Scenario #" << id << endl;

  int period[10][10];
  int cost[10][10][30];
  for (int i = 0; i < n; i++) {
    fill(period[i], period[i]+10, 0);
  }
  
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (i == j) continue;
      cin >> period[i][j];
      for (int k = 0; k < period[i][j]; k++) {
	cin >> cost[i][j][k];
      }
    }
  }

  // best[i][j] = best cost to end at city j after i flights
  int best[1001][10];

  fill(best[0], best[0]+n, -1);
  best[0][0] = 0;

  for (int d = 0; d < k; d++) {
    fill(best[d+1], best[d+1]+n, -1);
    for (int i = 0; i < n; i++) {
      if (best[d][i] < 0) continue;

      for (int j = 0; j < n; j++) {
	if (period[i][j] == 0 || i == j) continue;
	int c = cost[i][j][d % period[i][j]];
	if (c == 0) continue;
	int t = best[d][i] + c;

	if (best[d+1][j] < 0 || t < best[d+1][j]) {
	  best[d+1][j] = t;
	}
      }
    }
  }

  if (best[k][n-1] >= 0) {
    cout << "The best flight costs " << best[k][n-1] << "." << endl;
  } else {
    cout << "No flight possible." << endl;
  }
  
  cout << endl;
  return true;
}

int main()
{
  int id = 1;

  while (solve(id++))
    ;
  return 0;
}
