#include <bits/stdc++.h>

using namespace std;

int main()
{
  int N, iP;
  double P;
  
  cin >> N >> P;
  iP = int(P * 10000 + 0.5);

  int E[10001];
  fill(E, E+10001, INT_MAX);

  E[0] = 0;
  for (int i = 0; i < N; i++) {
    int e, ip;
    double p;
    cin >> e >> p;
    ip = int(p * 10000 + 0.5);

    for (int j = 10000; j >= 0; j--) {
      if (E[j] == INT_MAX) continue;
      E[ip+j] = min(E[ip+j], E[j] + e);
    }
  }

  int ans = *min_element(E+iP, E+10001);
  cout << ans << endl;

  return 0;
}
