// idea:
//
// from i = n/2+1 to n        =>  n/i = 1
// from i = n/3+1 to n/2      =>  n/i = 2
//
// etc.

#include <iostream>

using namespace std;

void solve()
{
  int n;
  cin >> n;

  long long ans = 0;
  int last = n;

  // roughly sqrt(2^31-1)
  for (int quot = 1; quot <= n && last > 46340; quot++) {
    int first = n/(quot+1) + 1;
    ans += quot * (last - first + 1);
    last = first-1;
  }
  for (int i = 1; i <= last; i++) {
    ans += n / i;
  }
  cout << ans << endl;
}

int main(void)
{
  int T;
  cin >> T;
  while (T--) {
    solve();
  }

  return 0;
}
