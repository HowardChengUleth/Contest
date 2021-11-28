#include <bits/stdc++.h>

using namespace std;

int main()
{
  string s;
  cin >> s;
  auto pos = s.find('a');
  cout << s.substr(pos) << endl;
  return 0;
}
