#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main()
{
  int n;
  cin >> n;

  ll ans = 1;   // (0,0)

  ll prev_a = 0, prev_b = 0;
  ll a, b;
  bool swapped = false;
  
  while (n-- > 0) {
    cin >> a >> b;
    if (swapped) {
      swap(a,b);
    }

    if (prev_a == a && prev_b == b)
      continue;

    if (prev_a > prev_b) {
      swap(prev_a, prev_b);
      swap(a, b);
      swapped = !swapped;
    }

    if (prev_b <= a) {
      ans += min(a, b) - prev_b + 1;
    }
    if (prev_a == prev_b) {
      ans--;
    }
    prev_a = a;
    prev_b = b;
  }

  cout << ans << endl;
  return 0;
}
