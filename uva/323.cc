#include <iostream>
#include <algorithm>
#include <cassert>

using namespace std;

const int MAX_N = 200;
const int MAX_M = 20;
const int MAX_DIFF = 2 * MAX_M * 20 + 1;

int n, m;
int p[MAX_N], d[MAX_N];

//
// Each subset can have |D(J) - P(J)| <= m*20 <= 400.
//

// best_sum[i][j][k] = the best sum of D(J) + P(J) possible for the subset
//                     with D(J) - P(J) = k, |J| = j, and after 0..i people
//                     have been considered
int best_sum[MAX_N][MAX_M+1][MAX_DIFF];
int choice[MAX_N][MAX_M+1][MAX_DIFF];

int ind(int diff)
{
  return diff + MAX_M*20;
}

int diff(int ind)
{
  return ind - MAX_M*20;
}

int compute(int i, int j, int k)
{
  if (k < 0 || k >= MAX_DIFF) {
    return -1;
  }
  if (best_sum[i][j][k] != -2) {
    return best_sum[i][j][k];
  }

  // empty set
  if (j == 0) {
    choice[i][j][k] = -1;
    if (diff(k) == 0) {
      best_sum[i][j][k] = 0;
    } else {
      best_sum[i][j][k] = -1;
    }
    return best_sum[i][j][k];
  }

  if (i == 0) {
    if (j > 1 || diff(k) != d[0] - p[0]) {
      choice[i][j][k] = -1;
      best_sum[i][j][k] = -1;
    } else {
      choice[i][j][k] = 1;
      best_sum[i][j][k] = d[0] + p[0];
    }
    return best_sum[i][j][k];
  }

  best_sum[i][j][k] = -1;
  choice[i][j][k] = -1;
  
  // don't include person i
  int temp_sum = compute(i-1, j, k);
  if (temp_sum >= 0) {
    best_sum[i][j][k] = temp_sum;
    choice[i][j][k] = 0;
  }

  // include person i
  int prev_k = k - (d[i] - p[i]);
  temp_sum = compute(i-1, j-1, prev_k);
  if (temp_sum >= 0) {
    int new_sum = temp_sum + d[i] + p[i];
    if (new_sum > best_sum[i][j][k]) {
      best_sum[i][j][k] = new_sum;
      choice[i][j][k] = 1;
    }
  }

  return best_sum[i][j][k];
}

void trace(int i, int j, int k)
{
  if (i < 0 || j == 0 || choice[i][j][k] < 0) {
    return;
  }
  if (choice[i][j][k]) {
    trace(i-1, j-1, k - (d[i] - p[i]));
    cout << ' ' << i+1;
  } else {
    trace(i-1, j, k);
  }
}

bool solve(int case_num)
{
  cin >> n >> m;
  if (!n && !m) return false;

  for (int i = 0; i < n; i++) {
    cin >> p[i] >> d[i];
  }
  
  for (int i = 0; i < n; i++) {
    for (int j = 0; j <= m; j++) {
      fill(best_sum[i][j], best_sum[i][j] + MAX_DIFF, -2);
    }
  }

  bool found = false;
  int best_S = -1;
  int best_D;
  for (int k = 0; k <= MAX_DIFF && !found; k++) {
    int S = compute(n-1, m, ind(k));
    if (S >= 0) {
      if (best_S == -1 || best_S < S) {
	best_S = S;
	best_D = k;
	found = true;
      }
    }

    S = compute(n-1, m, ind(-k));
    if (S >= 0) {
      if (best_S == -1 || best_S < S) {
	best_S = S;
	best_D = -k;
	found = true;
      }
    }
  }

  assert(best_S >= 0);
  int P = (best_S - best_D) / 2;
  int D = best_S - P;
  
  cout << "Jury #" << case_num << endl;
  cout << "Best jury has value " << P << " for prosecution and value "
       << D << " for defence:" << endl;

  trace(n-1, m, ind(best_D));
  cout << endl << endl;
  
  return true;
}

int main(void)
{
  int case_num = 1;
  while (solve(case_num++))
    ;

  return 0;
}
