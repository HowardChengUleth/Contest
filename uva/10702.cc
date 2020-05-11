#include <iostream>
#include <algorithm>

using namespace std;

bool solve()
{
  int C, S, E, T;
  cin >> C >> S >> E >> T;
  if (!C && !S && !E && !T) return false;

  S--; 

  int A[100][100];
  for (int i = 0; i < C; i++) {
    for (int j = 0; j < C; j++) {
      cin >> A[i][j];
    }
  }

  int ends[100];
  for (int i = 0; i < E; i++) {
    cin >> ends[i];
    ends[i]--;
  }
  
  // best[i][j] = max profit ending at i, after j trips
  int best[100][1001];
  for (int i = 0; i < C; i++) {
    fill(best[i], best[i]+T+1, -1);
  }
  best[S][0] = 0;

  for (int j = 1; j <= T; j++) {
    for (int i = 0; i < C; i++) {
      if (best[i][j-1] < 0) continue;
      for (int i2 = 0; i2 < C; i2++) {
	int temp = best[i][j-1] + A[i][i2];
	best[i2][j] = max(best[i2][j], temp);
      }
    }
  }

  int ans = -1;
  for (int i = 0; i < E; i++) {
    ans = max(ans, best[ends[i]][T]);
  }
  cout << ans << endl;
  
  return true;
}

int main()
{
  while (solve())
    ;
  return 0;
}
