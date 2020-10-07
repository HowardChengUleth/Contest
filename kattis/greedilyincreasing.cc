#include <bits/stdc++.h>

using namespace std;

int main()
{
  int n;

  cin >> n;
  
  vector<int> res;
  int a;
  
  cin >> a;
  res.push_back(a);

  for (int i = 1; i < n; i++) {
    cin >> a;
    if (res.back() < a) {
      res.push_back(a);
    }
  }

  cout << res.size() << endl;
  for (auto x : res) {
    cout << x << ' ';
  }
  cout << endl;
  
  
  return 0;
}
