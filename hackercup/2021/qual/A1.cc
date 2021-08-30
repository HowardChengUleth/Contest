#include <bits/stdc++.h>

using namespace std;

bool isVowel(char c)
{
  const string vowels = "AEIOU";
  return vowels.find(c) != string::npos;
}

void solve()
{
  string s;
  cin >> s;

  int ans = s.length() * 10;

  for (char f = 'A'; f <= 'Z'; f++) {
    int t = 0;
    for (auto c : s) {
      if (f == c) continue;
      t += (isVowel(f) == isVowel(c)) ? 2 : 1;
    }
    ans = min(ans, t);
  }

  cout << ans << endl;
}

int main()
{
  int T;
  cin >> T;
  for (int i = 1; i <= T; i++) {
    cout << "Case #" << i << ": ";
    solve();
  }
  return 0;
}
