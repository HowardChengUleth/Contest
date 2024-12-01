#include <bits/stdc++.h>

using namespace std;

int main()
{
  vector<int> L, R;
  int a, b;

  while (cin >> a >> b) {
    L.push_back(a);
    R.push_back(b);
  }

  map<int,int> Rfreq;
  for (auto x : R) {
    Rfreq[x]++;
  }

  long long ans = 0;
  for (auto x : L) {
    ans += x * Rfreq[x];
  }

  cout << ans << endl;


  return 0;
}
