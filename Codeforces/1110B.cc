#include <bits/stdc++.h>

using namespace std;

int main()
{
  int n, m, k;
  cin >> n >> m >> k;

  int b[100000], d[100000];
  for (int i = 0; i < n; i++) {
    cin >> b[i];
    if (i) {
      d[i-1] = b[i] - b[i-1] - 1;
    }
  }
  sort(d, d+n-1);
  int ans = b[n-1] - b[0] + 1;
  for (int i = 0; i < k-1; i++) {
    ans -= d[n-2-i];
  }
  cout << ans << endl;
  
  return 0;
}
