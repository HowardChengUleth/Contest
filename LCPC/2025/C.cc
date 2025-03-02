#include <bits/stdc++.h>

using namespace std;

bool palindrome(string s)
{
  string rev = s;
  reverse(begin(s), end(s));
  return s == rev;
}

int main()
{
  string s;
  cin >> s;

  int n = s.length();
  for (int i = 0; i < n; i++) {
    string t = s.substr(0, i);
    reverse(begin(t), end(t));
    if (palindrome(s + t)) {
      cout << i << endl;
      return 0;
    }
  }

  cout << n << endl;

  return 0;
}
