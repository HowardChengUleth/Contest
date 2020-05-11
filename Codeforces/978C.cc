#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main()
{
  int n, m;
  cin >> n >> m;

  ll a[200000], b[200000];
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  for (int i = 0; i < m; i++) {
    cin >> b[i];
  }

  int ai = 0;
  ll total = 0;

  for (int i = 0; i < m; i++) {
    while (total < b[i]) {
      total += a[ai++];
    }
    cout << ai << ' ' << b[i] - total + a[ai-1] << endl;
  }
  
  return 0;
}
