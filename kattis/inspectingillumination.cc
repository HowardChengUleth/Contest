#include <bits/stdc++.h>

using namespace std;

int main()
{
  int n;
  cin >> n;

  int mask = 1;
  int b[1001] = {0};

  while (true) {
    vector<int> v;
    v.reserve(1000);
    for (int i = 1; i <= n; i++) {
      if (i & mask) {
	v.push_back(i);
      }
    }
    if (v.size() == 0) break;
    cout << "ASK " << v.size();
    for (auto x : v) {
      cout << ' ' << x;
    }
    cout << endl;
    cout.flush();
    for (int i = 0; i < (int)v.size(); i++) {
      int x;
      cin >> x;
      b[x] |= mask;
    }
    mask <<= 1;
  }

  cout << "ANSWER";
  for (int i = 1; i <= n; i++) {
    cout << ' ' << b[i];
  }
  cout << endl;
  cout.flush();

  return 0;
}
