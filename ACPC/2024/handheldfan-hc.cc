#include <bits/stdc++.h>

using namespace std;

int main()
{
  int N, W;
  cin >> N >> W;

  W *= 60;
  vector<int> T(N);
  for (auto &x : T) {
    cin >> x;
  }

  int ans = 0;
  for (int start = 0; start < N; start++) {
    int sum = 0;
    int end = start;
    for (; end < N && sum + 2*T[end] <= W; end++) {
      sum += 2*T[end];
    }
    ans = max(ans, end - start);
  }

  cout << ans << endl;
  return 0;
}
