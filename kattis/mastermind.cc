#include <bits/stdc++.h>

using namespace std;

int main()
{
  int n;
  cin >> n;

  string s1, s2;
  cin >> s1 >> s2;

  int count1[256] = {0}, count2[256] = {0};
  for (auto c : s1) {
    count1[c]++;
  }
  for (auto c : s2) {
    count2[c]++;
  }

  int r = 0, s = 0;
  for (int i = 0; i < n; i++) {
    if (s1[i] == s2[i]) {
      r++;
    }
  }
  for (int i = 0 ; i < 256; i++) {
    s += min(count1[i], count2[i]);
  }
  s -= r;
  cout << r << ' ' << s << endl;
  
  return 0;
}
