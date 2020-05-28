#include <bits/stdc++.h>

using namespace std;

// If two boxes d_i and d_j sums up to be divisible by k, then the remainder
// of d_i and d_j mod k are additive inverses to each other.
//
// i.e. d_i = k-d_j mod k
//
// So we just have to count how many boxes there are of each remainder mod k,
// and match them up.  Only tricky part is when d_i = d_j mod k.  This happens
// when d_i = 0 and d_i = k/2 (when k is even).

int main()
{
  int rem[100] = {0};

  int n, k;
  cin >> n >> k;

  for (int i = 0; i < n; i++) {
    int d;
    cin >> d;
    rem[d%k]++;
  }

  int ans = rem[0]/2;
  for (int i = 1; i < k/2; i++) {
    ans += min(rem[i], rem[k-i]);
  }
  if (k % 2 == 0) {
    ans += rem[k/2]/2;
  } else {
    ans += min(rem[k/2], rem[k-k/2]);
  }
  ans *= 2;
  
  cout << ans << endl;


}
