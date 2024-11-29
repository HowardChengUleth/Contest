#include <bits/stdc++.h>

using namespace std;

void solve()
{
  int S;
  cin >> S;

  vector<int> B, R;
  for (int i = 0; i < S; i++) {
    int len;
    char color;
    cin >> len >> color;
    if (color == 'B') {
      B.push_back(len);
    } else {
      R.push_back(len);
    }
  }

  sort(rbegin(B), rend(B));
  sort(rbegin(R), rend(R));

  int n = min(B.size(), R.size());

  int ans = 0;
  for (int i = 0; i < n; i++) {
    ans += B[i] - 1;
    ans += R[i] - 1;
  }

  cout << ans << endl;
}

int main()
{
  int N;
  cin >> N;

  for (int i = 1; i <= N; i++) {
    cout << "Case #" << i << ": ";
    solve();
  }

  return 0;
}
