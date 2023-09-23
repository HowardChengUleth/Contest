#include <bits/stdc++.h>

using namespace std;

int main()
{
  string s;
  getline(cin, s);

  s.resize(unique(begin(s), end(s)) - begin(s));
  cout << s << endl;
  return 0;
}
