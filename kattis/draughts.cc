#include <bits/stdc++.h>

using namespace std;

const int dr[] = { -1, -1, 1, 1 };
const int dc[] = { -1, 1, -1, 1 };

int search(string A[10], int r, int c)
{
  int best = 0;
  for (int d = 0; d < 4; d++) {
    int r2 = r + dr[d], c2 = c + dc[d];
    int r3 = r2 + dr[d], c3 = c2 + dc[d];

    if (0 <= r3 && r3 < 10 && 0 <= c3 && c3 < 10 &&
	A[r2][c2] == 'B' && A[r3][c3] == '#') {
      A[r][c] = A[r2][c2] = '#';
      A[r3][c3] = 'W';
      best = max(best, 1 + search(A, r3, c3));
      A[r][c] = 'W';
      A[r2][c2] = 'B';
      A[r3][c3] = '#';
    }
  }
  return best;
}

void solve()
{
  string A[10];
  for (int i = 0; i < 10; i++) {
    cin >> A[i];
  }

  int best = 0;
  for (int r = 0; r < 10; r++) {
    for (int c = 0; c < 10; c++) {
      if (A[r][c] != 'W') continue;
      best = max(best, search(A, r, c));
    }
  }
  
  cout << best << endl;
}


int main()
{
  int T;
  cin >> T;

  for (int i = 0; i < T; i++) {
    solve();
  }

  return 0;
}
