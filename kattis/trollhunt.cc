#include <bits/stdc++.h>

using namespace std;

int main()
{
  int b, k, g;
  cin >> b >> k >> g;

  int ans = 0;
  while (b > 1) {
    ans++;
    b -= k/g;
  }
  cout << ans << endl;
  return 0;
}
