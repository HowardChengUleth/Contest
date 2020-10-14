#include <bits/stdc++.h>

using namespace std;

int main()
{
  int N;
  int t[100000];

  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> t[i];
  }
  sort(t, t+N);

  int ans = 0;
  for (int i = 1; i <= N; i++) {
    ans = max(ans, i + t[N-i]);
  }

  cout << ans+1 << endl;
  return 0;
}
