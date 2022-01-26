#include <bits/stdc++.h>

using namespace std;

pair<string, int> f(int x)
{
  if (!x) return { "", 0 };
  if (x % 2) {
    auto [s, t] = f(x-1);
    if (x == 1) {
      s += "1";
    } else {
      s += "1+";
      t++;
    }
    return {s, t};
  } else {
    auto [s, t] = f(x/2);
    s += "d+";
    t++;
    return {s, t};
  }
}

int main()
{
  int n;
  cin >> n;

  vector<int> x(n);
  for (auto &a : x) {
    cin >> a;
  }
  reverse(begin(x), end(x));

  vector<string> ans;
  int add = 0;
  for (int i = 0; i < n; i++) {
    auto [s, t] = f(x[i] + add);
    ans.push_back(s);
    add += t;
  }
  reverse(begin(ans), end(ans));
  for (auto s : ans) {
    cout << s;
  }
  cout << endl;
  
  return 0;
}
