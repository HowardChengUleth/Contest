#include <bits/stdc++.h>

using namespace std;

int main()
{
  int G, T, N, w;

  cin >> G >> T >> N;

  int ans = G - T;
  ans = ans * 9 / 10;
  for (int i = 0; i < N; i++) {
    cin >> w;
    ans -= w;
  }

  cout << ans << endl;

  return 0;
}
