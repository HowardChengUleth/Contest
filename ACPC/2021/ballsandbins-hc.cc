#include <bits/stdc++.h>

using namespace std;

int N;
int p[300];
int cump[300];

// number of bins with 0 balls, 1 balls, and 2 balls
// number of bins with 3 balls = N - total
double memo[101][101][101];

double f(int b0, int b1, int b2, int roll = 0, int sofar = 0)
{
  auto &ans = memo[b0][b1][b2];
  if (ans >= 0) {
    return ans;
  }

  if (roll >= 3*N || (!b0 && !b1 && !b2)) {
    return ans = sofar;
  }

  // we can always stop
  ans = sofar;

  sofar += p[roll];
  double ans2 = 0.0;
  if (b0 != 0) {
    ans2 += 1.0*b0 / N * f(b0-1, b1+1, b2, roll+1, sofar);
  }
  if (b1 != 0) {
    ans2 += 1.0*b1 / N * f(b0, b1-1, b2+1, roll+1, sofar);
  }
  if (b2 != 0) {
    ans2 += 1.0*b2 / N * f(b0, b1, b2-1, roll+1, sofar);
  }
  
  return ans = max(ans, ans2);
}

int main()
{
  cin >> N;
  for (int i = 0; i < 3*N; i++) {
    cin >> p[i];
  }
  
  for (int i = 0; i <= N; i++) {
    for (int j = 0; j <= N; j++) {
      for (int k = 0; k <= N; k++) {
	memo[i][j][k] = -1.0;
      }
    }
  }
  
  cout << fixed << setprecision(10) << f(N,0,0) << endl;
  
  return 0;
}
