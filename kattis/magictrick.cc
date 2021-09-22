#include <bits/stdc++.h>

using namespace std;

int main()
{
  string s;
  cin >> s;

  sort(s.begin(), s.end());
  if (unique(s.begin(), s.end()) == s.end()) {
    cout << 1 << endl;
  } else {
    cout << 0 << endl;
  }
  return 0;
}
