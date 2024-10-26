#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int m, n;
ll H[1000][1000];
ll speed[1000][1000];

ll solve(int r, int c)
{
  if (speed[r][c] != INT_MIN) {
    return speed[r][c];
  }

  if (r == 0 && c == 0) {
    return speed[r][c] = 0;
  }
  
  // look up
  if (r > 0 && solve(r-1, c) >= 0) {
    speed[r][c] = max(speed[r][c], solve(r-1, c) - 10 + (H[r-1][c] - H[r][c]));
  }

  // look left
  if (c > 0 && solve(r, c-1) >= 0) {
    speed[r][c] = max(speed[r][c], solve(r, c-1) - 10 + (H[r][c-1] - H[r][c]));
  }

  // look diagonal
  if (r > 0 && c > 0 && solve(r-1, c-1) >= 0) {
    speed[r][c] = max(speed[r][c], solve(r-1, c-1) - 15 + (H[r-1][c-1] - H[r][c]));
  }

  if (speed[r][c] == INT_MIN) {
    speed[r][c] = -1;
  }

  return speed[r][c];

}

int main()
{
  cin >> n >> m;
  for (int r = 0; r < n; r++) {
    for (int c = 0; c < m; c++) {
      cin >> H[r][c];
      speed[r][c] = INT_MIN;
    }
  }

  ll speed = solve(n-1, m-1);
  if (speed < 0) {
    cout << "TOO SLOW" << endl;
  } else {
    cout << speed << endl;
  }

  return 0;
}
