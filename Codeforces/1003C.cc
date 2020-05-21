#include <bits/stdc++.h>

using namespace std;

// the time limit is rather generous (4 seconds), so any O(n^2) algorithm
// should work.  We can just try all intervals.  To compute the sum of the
// range quickly, we can use partial sums (or we can also just add them up
// as we go).

int main()
{
  int n, k;
  cin >> n >> k;

  int a[5000];
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }

  int ps[5000];
  partial_sum(a, a+n, ps);
  
  double ans = 0.0;
  for (int i = 0; i < n; i++) {
    for (int j = i+k-1; j < n; j++) {
      int sum = ps[j];
      if (i > 0) {
	sum -= ps[i-1];
      }
      double avg = (double) sum / (j-i+1);
      ans = max(ans, avg);
    }
  }

  cout << fixed << setprecision(10) << ans << endl;

  return 0;
}
