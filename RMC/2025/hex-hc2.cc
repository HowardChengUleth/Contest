#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> pii;

pii combine(pii &curr, pii next)
{
  return pii(min(curr.first, next.first), max(curr.second, next.second));
}

pii minmax(string &s, int i = 0)
{
  if (i == s.length()) {
    if (s.length() > 1 && s[0] == '0') {
      return pii(INT_MAX, INT_MIN);
    }
    return pii(stoi(s, nullptr, 16), stoi(s, nullptr, 16));
  }

  char old = s[i];
  
  pii ans{INT_MAX, INT_MIN};
  
  if (s[i] == 'D' || s[i] == '0') {
    s[i] = '0';
    ans = combine(ans, minmax(s, i+1));
    s[i] = 'D';
    ans = combine(ans, minmax(s, i+1));
  } else if (s[i] == 'B' || s[i] == '8') {
    s[i] = '8';
    ans = combine(ans, minmax(s, i+1));
    s[i] = 'B';
    ans = combine(ans, minmax(s, i+1));
  } else {
    ans = combine(ans, minmax(s, i+1));
  }

  s[i] = old;
  return ans;
}

int main()
{
  int N;
  cin >> N;
  
  int maxsum = 0;
  int minsum = 0;
  for (int i = 0; i < N; i++) {
    string s;
    cin >> s;

    auto [mins, maxs] = minmax(s);
    maxsum += maxs;
    minsum += mins;
  }

  cout << hex << uppercase << maxsum << endl;
  cout << hex << uppercase << minsum << endl;

  return 0;
}
