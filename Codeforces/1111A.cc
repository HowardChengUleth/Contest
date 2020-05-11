#include <bits/stdc++.h>

using namespace std;

bool is_vowel(char c)
{
  string vowels = "aeiou";
  return vowels.find(c) != string::npos;
}

int main()
{
  string s, t;
  cin >> s >> t;

  if (s.length() != t.length()) goto no;
  for (int i = 0; i < s.length(); i++) {
    if (is_vowel(s[i]) ^ is_vowel(t[i])) goto no;
  }
  cout << "Yes" << endl;
  return 0;
  
 no:
  cout << "No" << endl;
  return 0;
}
