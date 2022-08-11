#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll gcd(ll a, ll b)
{
  if (!b) return a;
  return gcd(b, a%b);
}

ll solve(ll p, ll q)
{
  ll g = gcd(p, q);
  p /= g;
  q /= g;

  if (p == q) {
    return 1;
  }

  ll parP, parQ;
  if (p < q) {
    parP = p;
    parQ = q-p;

    // left child of parent
    return 2 * solve(parP, parQ);
  } else {
    parP = p-q;
    parQ = q;

    // right child
    return 2 * solve(parP, parQ) + 1;
  }
}

void solve()
{
  int C;
  ll p, q;
  char slash;

  cin >> C >> p >> slash >> q;
  cout << C << ' ' << solve(p, q) << endl;
}

int main()
{
  int P;
  cin >> P;

  for (int i = 0; i < P; i++) {
    solve();
  }
  
  return 0;
}
