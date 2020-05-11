#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main()
{
  int t;
  cin >> t;
  while (t--) {
    ll a, b;
    cin >> a >> b;

    if (2*b - a >= 0 && 2*a - b >= 0 &&
	(2*b - a) % 3 == 0 && (2*a - b) % 3 == 0) {
      cout << "YES" << endl;
    } else {
      cout << "NO" << endl;
    }

  }
  return 0;
}
