#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll s, r, m;

ll gcd(ll a, ll b)
{
  if (!b) return a;
  return gcd(b, a % b);
}

void rate(int t, ll &num, ll &denom)
{
  ll vol = 0;

  // maybe do geometric series...
  for (int i = 0; i < t; i++) {
    // add before multiply?  unclear from statement
    vol = min(vol + r, m);
    vol = min(vol * s, m);
  }

  num = vol;
  denom = t;

  ll g = gcd(num, denom);
  num /= g;
  denom /= g;
}

int main()
{
  cin >> s >> r >> m;
  ll best_num = 0, best_denom = 1, best_t = 0;
  for (int t = 1; t <= 40; t++) {
    ll num, denom;
    rate(t, num, denom);
    //    cout << "t = " << t << ", " << num << "/" << denom << endl;
    if (best_num * denom < num * best_denom) {
      best_denom = denom;
      best_num = num;
      best_t = t;
    }
  }
  cout << best_t << endl;
  
  return 0;
}
