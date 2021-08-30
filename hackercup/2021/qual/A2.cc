#include <bits/stdc++.h>

using namespace std;

const int INF = 10000;
int A[256][256];

void solve()
{
  string s;
  cin >> s;

  for (int i = 0; i < 256; i++) {
    fill(A[i], A[i]+256, INF);
    A[i][i] = 0;
  }
  int K;
  cin >> K;

  for (int i = 0; i < K; i++) {
    char c1, c2;
    cin >> c1 >> c2;
    A[c1][c2] = 1;
  }

  for (int k = 'A'; k <= 'Z'; k++) {
    for (int i = 'A'; i <= 'Z'; i++) {
      for (int j = 'A'; j <= 'Z'; j++) {
	A[i][j] = min(A[i][j], A[i][k] + A[k][j]);
      }
    }
  }
  
  int ans = s.length() * INF;
  for (char f = 'A'; f <= 'Z'; f++) {
    int t = 0;
    for (auto c : s) {
      if (A[c][f] < INF) {
	t += A[c][f];
      } else {
	t = ans;
	break;
      }
    }
    ans = min(ans, t);
  }

  cout << ((ans < s.length() * INF) ? ans : -1) << endl;
}

int main()
{
  int T;
  cin >> T;
  for (int i = 1; i <= T; i++) {
    cout << "Case #" << i << ": ";
    solve();
  }
  return 0;
}
