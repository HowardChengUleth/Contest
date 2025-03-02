#include <bits/stdc++.h>

using namespace std;

int main()
{
  int n;
  cin >> n;

  vector<int> s(n);
  for (auto &x : s) {
    cin >> x;
  }

  sort(begin(s), end(s));

  int lo = 0, hi = n-1;
  while (true) {
    if (lo > hi) break;
    cout << s[lo++] << ' ';

    if (lo > hi) break;
    cout << s[hi--] << ' ';
  }

  cout << endl;
  
  return 0;
}
