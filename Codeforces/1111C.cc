#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll n, k, A, B;
ll a[100000];

ll solve(int s, int e, int b)
{
  // if there are no avengers, then burning the base is always the best
  if (s == e) {
    return A;
  }

  // try burning it
  ll ans1 = B * (e-s) * (1LL << (n-b));
  ll ans2 = ans1;
  
  // try separating into 2, if interval is not of length 1
  if (n-b > 0) {
    ll prefix = (0xFFFFFFFFLL << (n-b)) & ((1LL << n) - 1);
    //cout << "  s, e, b = " << s << ' ' << e << ' ' << b << endl;
    assert((prefix & a[s]) == (prefix & a[e-1]));
    prefix &= a[s];
    //    cout << "  " << (prefix | (1LL << (n-b-1))) << endl;
    int m = lower_bound(a, a+k, (prefix | (1LL << (n-b-1)))) - a;
    
    ans2 = solve(s, m, b+1) + solve(m, e, b+1);
  }
  
  return min(ans1, ans2);
}

int main()
{
  cin >> n >> k >> A >> B;

  for (int i = 0; i < k; i++) {
    cin >> a[i];
    a[i]--;
  }
  sort(a, a+k);

  cout << solve(0, k, 0) << endl;

}
