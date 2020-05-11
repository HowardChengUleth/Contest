#include <iostream>

using namespace std;

// ways[s][d][m] = # of beautiful n-based numbers of length exactly m
//                 with the digits used in the bitmask s starting with digit
//                 d
int ways[1024][11][101];

const int MOD = 1000000007;

int compute(int s, int d, int m, int N)
{
  if (ways[s][d][m] >= 0) return ways[s][d][m];

  if (s == 0) {
    return ways[s][d][m] = (m == 0) ? 1 : 0;
  }
  if (m == 0) {
    // we know s != 0
    return ways[s][d][m] = 0;
  }
  
  if (m == 1) {
    return ways[s][d][m] = (s == (1 << d)) ? 1 : 0;
  }

  ways[s][d][m] = 0;
  if (s & (1 << d)) {
    if (d < N-1) {
      ways[s][d][m] += (compute(s, d+1, m-1, N) + 
			compute(s - (1 << d), d+1, m-1, N)) % MOD;
      ways[s][d][m] %= MOD;
    }
    if (d > 0) {
      ways[s][d][m] += (compute(s, d-1, m-1, N) + 
			compute(s - (1 << d), d-1, m-1, N)) % MOD;
      ways[s][d][m] %= MOD;
    }
  }

  return ways[s][d][m];
}

void solve()
{  
  int N, M;
  cin >> N >> M;

  for (int s = 0; s < (1 << N); s++) {
    for (int d = 0; d < N; d++) {
      for (int m = 0; m <= M; m++) {
	ways[s][d][m] = -1;
      }
    }
  }

  int total = 0;

  for (int m = 0; m <= M; m++) {
    for (int d = 1; d < N; d++) {
      total += compute((1 << N) - 1, d, m, N);
      total %= MOD;
    }
  }

  cout << total << endl;
}

int main()
{
  int T;
  cin >> T;
  while (T--)
    solve();
  return 0;
}
