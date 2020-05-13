#include <bits/stdc++.h>

using namespace std;

// the suffixes must match, so basically we are just asking for the longest
// common suffix

int main()
{
  string s1, s2;
  cin >> s1 >> s2;

  reverse(begin(s1), end(s1));
  reverse(begin(s2), end(s2));

  int p = 0;
  while (p < s1.length() && p < s2.length() && s1[p] == s2[p])
    p++;

  cout << s1.length() + s2.length() - 2*p << endl;
  return 0;
}
