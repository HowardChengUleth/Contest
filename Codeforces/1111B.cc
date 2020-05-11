#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main()
{
  ll n, k, m;
  cin >> n >> k >> m;

  ll A[100000];
  for (int i = 0; i < n; i++) {
    cin >> A[i];
  }
  sort(A, A+n);

  ll total = accumulate(A, A+n, 0LL);
  long double best = 0;

  for (ll r = 0; r < n && r <= m; r++) {
    ll left = n - r;
    long double avg = (long double)(total + min(k*left, m-r))/left;
    best = max(best, avg);
    total -= A[r];
  }

  cout << fixed << setprecision(16) << best << endl;
  
  return 0;
}
