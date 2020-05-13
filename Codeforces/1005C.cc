#include <bits/stdc++.h>

using namespace std;

// with a_i <= 10^9, a_i + a_j < 2^31.  So for each a_i we only need to know if
// we can get to 2^1, 2^2, ..., 2^30.  This can be done by a search to see
// if 2^k - a_i is in the set (taking care of the duplicates).

// apparently multiset is a lot slower than map...

int n;
int a[120000];

int main()
{
  cin.sync_with_stdio(false);
  cin.tie(0);
  
  map<int,int> S;
  
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    S[a[i]]++;
  }

  int ans = 0;
  for (int i = 0; i < n; i++) {
    bool found = false;
    for (int k = 1, p2 = 2; k <= 30 && !found; k++, p2 *= 2) {
      int partner = p2 - a[i];
      auto it = S.find(partner);
      int count = it == S.end() ? 0 : it->second;
      found = (partner == a[i] && count > 1) ||
	(partner != a[i] && count > 0);
    }
    if (!found) {
      ans++;
    }
  }

  cout << ans << endl;
  

  return 0;
}
