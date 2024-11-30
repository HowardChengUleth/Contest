#include <bits/stdc++.h>

using namespace std;

const string val[] = {
  "000", "001", "010", "011", "100", "101", "110", "111"
};

int main()
{
  string s;
  cin >> s;

  while (s.length() % 3 != 0) {
    s = string("0") + s;
  }
  for (int i = 0; i < s.length(); i += 3) {
    cout << find(val, val+8, s.substr(i, 3)) - val;
  }
  cout << endl;
  return 0;
}
