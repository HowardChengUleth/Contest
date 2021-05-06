#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

bool isvowel(char c)
{
  const string vowels = "AEIOU";
  return vowels.find(c) != string::npos;
}

ll solve(string &s, int index, ll mult)
{
  if (index >= s.length()) {
    if (s.find('L') == string::npos) return 0;
    int vc = 0, cc = 0;
    if (isvowel(s[0])) {
      vc = 1;
    } else {
      cc = 1;
    }

    for (int i = 1; i < s.length(); i++) {
      if (isvowel(s[i])) {
	cc = 0;
	vc++;
	if (vc >= 3) {
	  return 0;
	}
      } else {
	vc = 0;
	cc++;
	if (cc >= 3) {
	  return 0;
	}
      }
    }

    return mult;
  } else {
    if (s[index] != '_') {
      return solve(s, index+1, mult);
    }

    ll ans = 0;
    s[index] = 'L';
    ans += solve(s, index+1, mult);

    s[index] = 'A';
    ans += solve(s, index+1, mult*5);
    
    s[index] = 'B';
    ans += solve(s, index+1, mult*20);

    s[index] = '_';

    //    cout << "f(" << index << ") = " << ans << endl;
    return ans;
  }
}

int main()
{
  string s;
  cin >> s;

  cout << solve(s, 0, 1) << endl;
  
  return 0;
}
