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

  sort(begin(L), end(L));
  sort(begin(R), end(R));

  int ans = 0;
  for (int i = 0; i < L.size(); i++) {
    ans += abs(L[i] - R[i]);
  }

  cout << ans << endl;


  return 0;
}
