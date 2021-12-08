#include <bits/stdc++.h>

using namespace std;

int decode(string s[], string out[])
{
  string segs[] = { "abcefg", "cf", "acdeg", "acdfg", "bcdf",
		    "abdfg", "abdefg", "acf", "abcdefg", "abcdfg" };

  string perm = "abcdefg";

  do {
    bool bad = false;
    int digit[10];
    for (int i = 0; i < 10 && !bad; i++) {
      string t;
      for (auto c : s[i]) {
	t += perm[c - 'a'];
      }
      sort(begin(t), end(t));
      int d = find(segs, segs+10, t) - segs;
      if (d == 10) {
	bad = true;
      } else {
	digit[i] = d;
      }
    }
    for (int i = 0; i < 10 && !bad; i++) {
      bad |= (count(digit, digit+10, i) != 1);
    }
    if (bad) continue;

    int ans = 0;
    for (int i = 0; i < 4; i++) {
      int t = find(s, s+10, out[i]) - s;
      ans = ans * 10 + digit[t];
    }
    return ans;
  } while (next_permutation(begin(perm), end(perm)));

  assert(false);
  return -1;
}

int main()
{
  int ans = 0;
  while (true) {
    string s[11];
    for (int i = 0; i < 11; i++) {
      if (!(cin >> s[i])) goto out;
      sort(begin(s[i]), end(s[i]));
    }
    string out[4];
    for (int i = 0; i < 4; i++) {
      cin >> out[i];
      sort(begin(out[i]), end(out[i]));
    }
    ans += decode(s, out);
  }
 out:
  cout << ans << endl;

  return 0;
}
