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

  cout << accumulate(begin(v), end(v), 0) << endl;
  return 0;
}
