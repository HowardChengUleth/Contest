#include <bits/stdc++.h>

using namespace std;

// to be able to get to 1 after dividing by 6, it must be true that
// n = 2^a * 3^b where a <= b.  The number of moves is (b-a) + b

void solve()
{
  int a = 0, b = 0;
  int n;
  cin >> n;

  while (n % 2 == 0) {
    n /= 2;
    a++;
  }
  while (n % 3 == 0) {
    n /= 3;
    b++;
  }
  if (a <= b && n == 1) {
    cout << 2*b-a << endl;
  } else {
    cout << -1 << endl;
  }

}

int main()
{
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}
