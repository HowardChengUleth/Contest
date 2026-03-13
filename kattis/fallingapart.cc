#include <bits/stdc++.h>

using namespace std;

int main()
{
  int n;
  cin >> n;

  vector<int> v(n);
  for (auto &x : v) {
    cin >> x;
  }

  sort(rbegin(v), rend(v));

  int value[2] = {0};
  for (int i = 0; i < n; i++) {
    value[i%2] += v[i];
  }

  cout << value[0] << ' ' << value[1] << endl;

  return 0;
}
