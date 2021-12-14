#include <bits/stdc++.h>

using namespace std;

typedef pair<char,char> pss;
map<pss, char> rule;

string apply(const string &s)
{
  int n = s.length();

  string t;
  for (int i = 0; i < n-1; i++) {
    t += s[i];
    t += rule[pss(s[i], s[i+1])];
  }
  t += s[n-1];

  return t;
}

int main()
{
  string s, blank;

  getline(cin, s);
  getline(cin, blank);

  string from, arrow;
  char to;
  while (cin >> from >> arrow >> to) {
    pss p(from[0], from[1]);
    rule[p] = to;
  }

  for (int i = 0; i < 10; i++) {
    s = apply(s);
  }

  int freq[256] = {0};
  for (auto c : s) {
    freq[c]++;
  }
  int maxf = 0, minf = INT_MAX;
  for (int i = 0; i < 256; i++) {
    if (!freq[i]) continue;
    maxf = max(maxf, freq[i]);
    minf = min(minf, freq[i]);
  }
  cout << maxf - minf << endl;
  

  return 0;
}
