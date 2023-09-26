#include <bits/stdc++.h>

using namespace std;

bool arithmetic(const vector<int> &v)
{
  int diff = v[1] - v[0];
  for (int i = 0; i < v.size()-1; i++) {
    if (v[i+1] - v[i] != diff) {
      return false;
    }
  }
  return true;
}

void solve()
{
  int m;
  cin >> m;

  vector<int> v(m);
  for (auto &x : v) {
    cin >> x;
  }

  if (arithmetic(v)) {
    cout << "arithmetic" << endl;
  } else {
    sort(begin(v), end(v));
    if (arithmetic(v)) {
      cout << "permuted arithmetic" << endl;
    } else {
      cout << "non-arithmetic" << endl;
    }
  }
}

int main()
{
  int n;
  cin >> n;

  for (int i = 0; i < n; i++) {
    solve();
  }
  
  return 0;
}
