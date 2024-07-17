#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main()
{
  ll r;
  cin >> r;
  
  ll r2 = r*r;
  ll best_x = r+1, best_y = 0;
  ll best_dist2 = best_x * best_x;
  for (ll x = 0; x <= r+1; x++) {
    ll y2 = r2 - x*x;
    ll y = ceil(sqrt(y2));
    if (y*y == y2) {
      y++;
    }

    ll dist2 = x*x + y*y;
    if (dist2 < best_dist2) {
      best_dist2 = dist2;
      best_x = x;
      best_y = y;
    }
  }

  cout << best_x << ' ' << best_y << endl;
  

  return 0;
}
