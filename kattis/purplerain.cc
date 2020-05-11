#include <bits/stdc++.h>

using namespace std;

int main()
{
  string s;
  cin >> s;

  int min_v = 0, min_index = 0;
  int max_v = 0, max_index = 0;

  int val = 0;
  for (int i = 0; i < s.length(); i++) {
    val += (s[i] == 'B') ? 1 : -1;
    if (val > max_v) {
      max_v = val;
      max_index = i+1;
    }
    if (val < min_v) {
      min_v = val;
      min_index = i+1;
    }
  }

  cout << min(min_index, max_index)+1 << ' ' << max(min_index, max_index) << endl;

  return 0;
}
