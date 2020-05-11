#include <iostream>
#include <algorithm>

using namespace std;

const int MAX_N = 75*2;

int A[MAX_N][MAX_N];
int hsum[MAX_N][MAX_N][MAX_N];
int n;

int max_vsum(int i, int j)
{
  int k;
  int best, best_end;
  int bestn, bestn_end;

  int total = 0;
  for (k = 0; k < n; k++) {
    total += hsum[i][j][k];
  }

  best = best_end = 0;
  bestn = bestn_end = 0;

  for (k = 0; k < n; k++) {
    best_end = max(best_end + hsum[i][j][k], 0);
    best = max(best, best_end);
    
    bestn_end = max(bestn_end - hsum[i][j][k], 0);
    bestn = max(bestn, bestn_end);
  }
  
  return max(best, total + bestn);
}

void solve()
{
  int i, j, k;
  int best;

  cin >> n;
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      cin >> A[i][j];
      A[i][j+n] = A[i][j];
    }
  }

  /* compute hsum */
  for (i = 0; i < n; i++) {
    for (k = 0; k < n; k++) {
      hsum[i][i][k] = A[k][i];
    }
  }

  for (i = 0; i < n; i++) {
    for (j = i+1; j < i+n; j++) {
      for (k = 0; k < n; k++) {
	hsum[i][j][k] = hsum[i][j-1][k] + A[k][j];
      }
    }
  }

  best = 0;
  for (i = 0; i < n; i++) {
    for (j = i; j < i+n; j++) {
      best = max(best, max_vsum(i, j));
    }
  }

  int large = -100;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      large = max(large, A[i][j]);
    }
  }


  if (large < 0) {
    cout << large << endl;
  } else {
    cout << best << endl;
  }
}

int main(void)
{
  int T;
  cin >> T;
  while (T--)
    solve();
  return 0;
}

