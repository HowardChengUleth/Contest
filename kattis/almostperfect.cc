#include <bits/stdc++.h>

using namespace std;

typedef int64_t ll;

// sum of divisors for p^k
ll sumofdiv(ll p, int k)
{
  ll ans = 1;
  for (int i = 0; i <= k; i++) {
    ans *= p;
  }
  ans -= 1;
  ans /= (p-1);
  return ans;
}
	    
string solve(ll n)
{
  ll orign = n;
  
  ll sum = 1;
  for (ll p = 2; p * p <= n; p++) {
    int k = 0;
    while (n % p == 0) {
      n /= p;
      k++;
    }
    if (k > 0) {
      sum *= sumofdiv(p, k);
    }
  }
  if (n > 1) {
    sum *= sumofdiv(n, 1);
  }

  sum -= orign;

  if (sum == orign) {
    return "perfect";
  } else if (abs(sum - orign) <= 2) {
    return "almost perfect";
  } else {
    return "not perfect";
  }
}


int main()
{
  int n;
  while (cin >> n) {
    cout << n << ' ' << solve(n) << endl;
  }

  return 0;
}
