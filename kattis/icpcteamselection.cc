#include <bits/stdc++.h>

using namespace std;

void solve()
{
  int N;
  cin >> N;
  vector<int> v(3*N);

  for (auto &x : v) {
    cin >> x;
  }
  sort(begin(v), end(v));

  int ans = 0;
  for (int i = 0; i < N; i++) {
    ans += v[3*N-2-2*i];
  }

  cout << ans << endl;

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
