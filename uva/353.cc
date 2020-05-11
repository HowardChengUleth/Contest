#include <iostream>
#include <string>
#include <set>

using namespace std;

bool palindrome(const string &s)
{
  for (unsigned int i = 0; i < s.length()/2; i++) {
    if (s[i] != s[s.length()-1-i]) {
      return false;
    }
  }
  return true;
}

void solve(const string &s)
{
  set<string> S;

  for (unsigned int i = 0; i < s.length(); i++) {
    for (unsigned int j = 1; j <= s.length()-i; j++) {
      S.insert(s.substr(i, j));
    }
  }
  
  int count = 0;
  for (set<string>::const_iterator it = S.begin(); it != S.end(); ++it) {
    if (palindrome(*it)) {
      count++;
    }
  }

  cout << "The string '" << s << "' contains " << count << " palindromes."
       << endl;


}

int main(void)
{
  string s;

  while (cin >> s) {
    solve(s);
  }

  return 0;
}
