#include <bits/stdc++.h>

using namespace std;

int main()
{
  int m, p, n;
  cin >> m >> p >> n;

  double perc = p / 100.0;

  int ans = 0;
  int target = m;
  for (int i = 0; i < n; i++) {
    int w;
    cin >> w;

    if (w >= target) {
      ans++;
    }

    int excess = w-target;
    target = ceil(m - excess*perc);
  }

  cout << ans << endl;
  return 0;
}
