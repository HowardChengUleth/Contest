#include <bits/stdc++.h>

using namespace std;

int main()
{
  int n;
  cin >> n;

  map<int,long long> M;
  for (int i = 0; i < n; i++) {
    int b;
    cin >> b;
    M[b-i] += b;
  }

  long long ans = LLONG_MIN;
  for (auto p : M) {
    ans = max(ans, p.second);
  }
  cout << ans << endl;
  return 0;
}
