#include <bits/stdc++.h>

using namespace std;

// the idea is that the first and last letter won't be repeated, but
// everything else will be, so we just remove the duplicates

int main()
{
  int t;
  cin >> t;
  while (t--) {
    string s;
    cin >> s;

    cout << s[0];
    for (int i = 2; i < s.length(); i += 2) {
      cout << s[i];
    }
    cout << s[s.length()-1] << endl;
  }

  
  return 0;
}
