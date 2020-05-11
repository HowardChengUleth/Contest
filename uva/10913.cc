#include <iostream>
#include <algorithm>
#include <climits>

using namespace std;

int grid[75][75];
int best[75][75][6][2][2];
bool init[75][75][6][2][2];
int N, k;

int compute(int i, int j, int k, bool to_left = true, bool to_right = true)
{
  if (init[i][j][k][to_left][to_right]) {
    return best[i][j][k][to_left][to_right];
  }

  if (i == N-1 && j == N-1) {
    if (grid[i][j] >= 0) {
      init[i][j][k][to_left][to_right] = true;
      return best[i][j][k][to_left][to_right] = grid[i][j];
    } else {
      init[i][j][k][to_left][to_right] = true;
      return best[i][j][k][to_left][to_right] = (k > 0) ? grid[i][j] : INT_MIN;
    }
  }

  if (k == 0 && grid[i][j] < 0) {
    init[i][j][k][to_left][to_right] = true;
    return best[i][j][k][to_left][to_right] = INT_MIN;
  }

  int k2 = (grid[i][j] < 0) ? k-1 : k;
  int temp;
  best[i][j][k][to_left][to_right] = INT_MIN;

  // try to move right
  if (j+1 < N && to_right) {
    if ((temp = compute(i, j+1, k2, false, true)) != INT_MIN) {
      best[i][j][k][to_left][to_right] = grid[i][j] + temp;
    }
  }

  // try to move down
  if (i+1 < N) {
    if ((temp = compute(i+1, j, k2)) != INT_MIN) {
      best[i][j][k][to_left][to_right] = 
	max(best[i][j][k][to_left][to_right], grid[i][j] + temp);
    }
  }

  // try to move left
  if (j-1 >= 0 && to_left) {
    if ((temp = compute(i, j-1, k2, true, false)) != INT_MIN) {
      best[i][j][k][to_left][to_right] = 
	max(best[i][j][k][to_left][to_right], grid[i][j] + temp);
    }
  }
  
  init[i][j][k][to_left][to_right] = true;
  return best[i][j][k][to_left][to_right];
}

bool solve(int id)
{
  cin >> N >> k;
  if (!N && !k) return false;

  cout << "Case " << id << ": ";
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cin >> grid[i][j];
    }
  }

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      for (int k = 0; k < 6; k++) {
	init[i][j][k][0][0] = false;
	init[i][j][k][0][1] = false;
	init[i][j][k][1][0] = false;
	init[i][j][k][1][1] = false;
      }
    }
  }

  if (compute(0, 0, k) == INT_MIN) {
    cout << "impossible" << endl;
  } else {
    cout << compute(0, 0, k) << endl;
  }
  return true;
}

int main()
{
  int id = 1;
  while (solve(id++))
    ;

  return 0;
}
