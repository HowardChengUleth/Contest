#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main()
{
  ll Au, Bu, Ar, Br;
  cin >> Au >> Bu >> Ar >> Br;

  ll ans = 0;
  
  // each unique A can be matched with reusable B if there are any.
  // otherwise it has to match with unique B
  if (Br > 0) {
    ans += Au;
    Au = 0;
  } else {
    ll match = min(Au, Bu);
    ans += match;
    Au -= match;
    Bu -= match;
  }

  // do the same for B
  if (Ar > 0) {
    ans += Bu;
    Bu = 0;
  } else {
    ll match = min(Au, Bu);
    ans += match;
    Au -= match;
    Bu -= match;
  }

  // all combinations of reuseable ones
  ans += Ar * Br;
  cout << ans << endl;
  
  return 0;
}
