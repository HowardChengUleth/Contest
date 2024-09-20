#include <bits/stdc++.h>

using namespace std;

bool check_len(string s, int start, int len)
{
  if (start+len > s.length())
    return false;

  int freq[26] = {0};
  for (int i = start; i < start+len; i++) {
    freq[s[i] - 'a']++;
  }
  int val = *max_element(freq, freq+26);
  for (int i = 0; i < 26; i++) {
    if (freq[i] != val && freq[i] != 0) {
      return false;
    }
  }

  return true;
}

int main()
{
  int n;
  string s;
  cin >> n >> s;

  for (int len = n; len >= 1; len--) {
    for (int i = 0; i < n; i++) {
      if (check_len(s, i, len)) {
	cout << len << endl;
	return 0;
      }
    }
  }

  assert(false);

  return 0;
}
