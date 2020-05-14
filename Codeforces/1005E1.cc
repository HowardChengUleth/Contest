#include <bits/stdc++.h>

using namespace std;

// Since it is a permutation, there is exactly one entry equal to m.  Let's
// say it is at index t.
//
// So the left and right boundaries of the interval [l, r] must contain t.
// Moreover, if L is the number of elements in the range < m, and U is the
// number of elements in this range > m, then we must have either
//
//    L   = U  (if range is odd)
//    L+1 = U  (if range is even)
//
// For a given range, we can easily compute L and U if we have arrays such
// that L[i] = number of elements < m from index 0, ..., i, and U[i] for
// elements > m.  (Actually you only need one of these arrays because the
// other one can be computed from the first one.)
//
// We still cannot afford to check all pairs (l,r) because it will be
// quadratic.
//
// Let's rethink.  The two conditions above can be rephrased as:
//
//   U-L = 0
//   U-L = 1
//
// How does that help?  If we define diff[i] = U[i] - L[i], then we now
// want diff[r] - diff[l-1] = 0 or 1.  i.e.
//
// diff[l-1] = diff[r] or
// diff[l-1] = diff[r]-1
//
// So: store the multiset S of all diff[0..t-1] values.  For each r >= t, ask
// how many times diff[r] and diff[r]-1 appears in S.  That's the total
// number of [l,r] with that right endpoint.  Don't forget the special case
// of l = 0.
//
// Total run time O(n log n)

int main()
{
  int n, m;
  cin >> n >> m;

  // technically I can do it all in one loop without explicitly
  // storing all entries of p or diff, but we will do it slowly to
  // be more clear
  int p[200000];
  int t = n;
  for (int i = 0; i < n; i++) {
    cin >> p[i];
    if (p[i] == m) {
      t = i;
    }
  }

  int diff[200000];
  map<int,int> S;

  long long ans = 0;
  for (int i = 0; i < n; i++) {
    int last = (i == 0) ? 0 : diff[i-1];
    diff[i] = last;
    if (p[i] > m) diff[i]++;
    if (p[i] < m) diff[i]--;
    if (i < t) {
      S[diff[i]]++;
    } else {
      if (diff[i] == 0 || diff[i] == 1) {
	// special case [0,i]
	ans++;
      }
      auto it1 = S.find(diff[i]);
      auto it2 = S.find(diff[i]-1);
      if (it1 != S.end()) {
	ans += it1->second;
      }
      if (it2 != S.end()) {
	ans += it2->second;
      }
    }
  }

  cout << ans << endl;
  return 0;
}
