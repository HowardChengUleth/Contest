#include <bits/stdc++.h>

using namespace std;

bool check()
{
  int n;
  cin >> n;
  vector<int> v(n);
  for (auto &x : v) {
    cin >> x;
  }

  vector<int> rightmax(n);
  rightmax[n-1] = -1;
  for (int i = n-2; i >= 0; i--) {
    rightmax[i] = max(rightmax[i+1], v[i+1]);
  }

  set<int> left;
  left.insert(v[0]);
  for (int i = 1; i < n; i++) {
    auto it = left.upper_bound(v[i]);
    if (it != left.end() && *it < rightmax[i]) {
      return true;
    }
    left.insert(v[i]);
  }

  return false;
}

int main()
{
  int k;
  cin >> k;

  set<int> ans;
  for (int i = 1; i <= k; i++) {
    if (check()) {
      ans.insert(i);
    }
  }

  cout << ans.size() << endl;
  for (auto x : ans) {
    cout << x << endl;
  }

  return 0;
}
