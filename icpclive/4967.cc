// DP from the bottom row and work your way up
//
#include <iostream>
#include <algorithm>
#include <climits>

using namespace std;

const int MAX_N = 100000;

bool solve(int id)
{
  int N;
  cin >> N;
  if (!N) return false;

  int grid[MAX_N][3];
  for (int i = 0; i < N; i++) {
    cin >> grid[i][0] >> grid[i][1] >> grid[i][2];
  }

  // we could have overwritten the previous array...
  int best[MAX_N][3];

  best[N-1][2] = INT_MAX;
  best[N-1][1] = grid[N-1][1];
  best[N-1][0] = grid[N-1][0] + grid[N-1][1];

  for (int i = N-2; i >= 0; i--) {
    best[i][2] = min(best[i+1][1], best[i+1][2]) + grid[i][2];
    best[i][1] = min(min(best[i][2], best[i+1][0]),
		     min(best[i+1][1], best[i+1][2])) + grid[i][1];
    best[i][0] = min(min(best[i][1], best[i+1][0]), best[i+1][1]) +
      grid[i][0];
  }

  cout << id << ". " << best[0][1] << endl;
  
  return true;
}

int main()
{
  int id = 1;
  while (solve(id++))
    ;
  return 0;
}
