#include <bits/stdc++.h>

using namespace std;

string s, t;
int memo[400][400];

bool solve(int N, int M)
{
  if (N == 0 && M == 0) {
    return true;
  }
  if (N == 0 && M > 0) {
    return false;
  }
  
  if (M == 0) {
    // can always do empty string
    return true;
  }

  if (memo[N][M] != -1) {
    return memo[N][M];
  }
  
  // try different last portion
  for (int len = 1; len <= N; len++) {
    // try exp = 0
    if (solve(N-len, M)) {
      return memo[N][M] = true;
    }

    // try using exp > 0
    for (int exp = 1; exp * len <= M; exp++) {
      bool match = true;
      for (int j = 0; j < len; j++) {
	match &= (s[N-len+j] == t[M-exp*len+j]);
      }
      if (match) {
	if (solve(N-len, M-exp*len)) {
	  return memo[N][M] = true;
	}
      } else {
	// no more matches
	break;
      }
    }
  }

  return memo[N][M] = false;
}

int main()
{
  int N, M;
  cin >> N >> M;
  cin >> s >> t;

  for (int i = 0; i <= N; i++) {
    for (int j = 0; j <= M; j++) {
      memo[i][j] = -1;
    }
  }

  cout << (solve(N, M) ? "yes" : "no") << endl;
  
  return 0;
}
