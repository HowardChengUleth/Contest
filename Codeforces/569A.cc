#include <bits/stdc++.h>

using namespace std;

// The idea is that as you listen to the first S seconds, you would have
// downloaded S*(q-1)/q seconds of songs.  As you listen to that part, you
// would have downloaded S*(q-1)^2/q^2 seconds of songs, etc.
//
// So for the first segment would listen to this many seconds of songs:
//
// S + S(q-1)/q + S(q-1)^2/q^2 + ... = S*(1/(1-(q-1)/q)) = S*q
//
// If this is not all of T, then we can use that as the new S and try again,
// so that will be S'*q = S*q*q = S*q^2
//
// If this is still not enough, then we listen again, this time for S*q^3
// seconds, etc.  This will not take too long before it is larger than T.

typedef long long ll;

int main()
{
  ll T, S, q;
  cin >> T >> S >> q;

  int ans = 1;
  while (S*q < T) {
    ans++;
    S *= q;
  }
  cout << ans << endl;

  return 0;
}
