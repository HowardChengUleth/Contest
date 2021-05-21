#include <bits/stdc++.h>

using namespace std;

int main()
{
  int n, m;
  cin >> n >> m;

  int can[100000];
  for (int i = 0; i < n; i++) {
    cin >> can[i];
  }
  sort(can, can+n);

  long long ans = 0;
  for (int i = 0; i < m; i++) {
    int x;
    cin >> x;

    ans += *lower_bound(can, can+n, x) - x;
  }
  cout << ans << endl;
  return 0;
}
