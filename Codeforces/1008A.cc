#include <bits/stdc++.h>

using namespace std;

// just do it...

bool isvowel[256];

int main()
{
  string s;
  cin >> s;

  isvowel['a'] = isvowel['e'] = isvowel['i'] = isvowel['o']
    = isvowel['u'] = true;

  for (int i = 0; i < s.length()-1; i++) {
    if (isvowel[s[i]] || s[i] == 'n') continue;
    if (!isvowel[s[i+1]]) {
      cout << "NO" << endl;
      return 0;
    }
  }
  char last = s[s.length()-1];
  if (last != 'n' && !isvowel[last]) {
    cout << "NO" << endl;
  } else {
    cout << "YES" << endl;
  }
  return 0;
}
