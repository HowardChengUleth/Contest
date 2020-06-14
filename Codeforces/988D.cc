#include <bits/stdc++.h>

using namespace std;

// first, the answer is always >= 1.
//
// The next observation is that the answer is <= 3.  If there are four points
// it is not hard to see that the pairwise distances cannot all be powers of
// 2.
//
// So we check to see if the answer is 3: in that case the three points must
// be separated by the same power of 2.  Note that it cannot be more than 2^30.
// So we can try for each point p, is p+2^k and p+2^(k+1) in the set.  If so
// we are done
//
// Similarly we can check for the answer = 2 case the same way

typedef long long ll;

int main()
{
  set<ll> S;
  int n;

  cin >> n;
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    S.insert(x);
  }

  // check for answer = 3
  for (auto x : S) {
    for (int k = 0; k <= 30; k++) {
      ll dist = 1LL << k;
      if (S.count(x+dist) && S.count(x+2*dist)) {
	cout << 3 << endl;
	cout << x << ' ' << x+dist << ' ' << x+2*dist << endl;
	return 0;
      }
    }
  }

  // check fo answer = 2
  for (auto x : S) {
    for (int k = 0; k <= 30; k++) {
      ll dist = 1LL << k;
      if (S.count(x+dist)) {
	cout << 2 << endl;
	cout << x << ' ' << x+dist << endl;
	return 0;
      }
    }
  }

  cout << 1 << endl;
  cout << *S.begin() << endl;

  return 0;
}
