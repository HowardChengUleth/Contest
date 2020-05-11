#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main()
{
  ll p[200000], q[200000];
  int n;
  cin >> n;
  for (int i = 0; i < n-1; i++) {
    cin >> q[i];
  }
  partial_sum(q, q+n-1, p);
  int m = *min_element(p, p+n-1);
  p[0] = 1 - min(0,m);
  for (int i = 0; i < n-1; i++) {
    p[i+1] = p[i] + q[i];
  }

  copy(p, p+n, q);
  sort(q, q+n);
  int u = unique(q, q+n) - q;
  
  if (u != n || *min_element(p, p+n) != 1 || *max_element(p, p+n) != n) {
    cout << -1 << endl;
  } else {
    for (int i = 0; i < n; i++) {
      cout << p[i] << ' ';
    }
    cout << endl;
  }
  
  return 0;
}
