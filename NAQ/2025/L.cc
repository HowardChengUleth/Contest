#include <bits/stdc++.h>

using namespace std;

int main()
{
  int n;
  cin >> n;

  vector<int> obs(n);
  for (auto &d : obs) {
    cin >> d;
  }

  vector<int> ans;
  ans.push_back(obs[0]/3);
  ans.push_back(obs[1] - ans[0]*2);
  ans.push_back(obs[n-1]/3);

  for (auto x : ans) {
    cout << x << ' ';
  }
  cout << endl;


  return 0;
}
