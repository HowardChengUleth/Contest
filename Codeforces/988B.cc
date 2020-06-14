#include <bits/stdc++.h>

using namespace std;

// in order for one string to be a substring of another, it must be the case
// that the first string is shorter than the second, or the two strings are the
// same.  So the only way this would work is if the strings are sorted in
// increasing length.  So just do that and check

int main()
{
  int n;
  cin >> n;

  string s[100];
  for (int i = 0; i < n; i++) {
    cin >> s[i];
  }

  sort(s, s+n, [](string a, string b) { return a.length() < b.length(); });
  for (int i = 0; i < n-1; i++) {
    if (s[i+1].find(s[i]) == string::npos) {
      cout << "NO" << endl;
      return 0;
    }
  }
  cout << "YES" << endl;
  for (int i = 0; i < n; i++) {
    cout << s[i] << endl;
  }
  
  return 0;
}
