#include <bits/stdc++.h>

using namespace std;

int main()
{
  string s;
  cin >> s;

  int n = s.length();

  int freq[3] = {0};
  long long ans = 0;
  
  for (int i = 0; i < n; i++) {
    int val = s[i] - '0';
    for (int j = val+1; j < 3; j++) {
      ans += freq[j];
    }
    freq[val]++;
  }

  cout << ans << endl;
  return 0;
}
