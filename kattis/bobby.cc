#include <bits/stdc++.h>

using namespace std;

int binom[11][11];

void solve()
{
  int R, S, X, Y, W;

  cin >> R >> S >> X >> Y >> W;

  double prob = 0.0;
  while (X <= Y) {
    // roll >= R exactly X times
    prob += binom[Y][X] * pow((S-(R-1.0))/S, X) * pow((R-1.0)/S, Y-X);
    X++;
  }

  if (prob * W > 1) {
    cout << "yes" << endl;
  } else {
    cout << "no" << endl;
  }
}

int main()
{
  for (int n = 0; n <= 10; n++) {
    binom[n][0] = binom[n][n] = 1;
    for (int k = 1; k < n; k++) {
      binom[n][k] = binom[n-1][k-1] + binom[n-1][k];
    }
  }
  
  int N;
  cin >> N;
  while (N--) {
    solve();
  }

  return 0;
}
