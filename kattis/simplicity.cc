#include <bits/stdc++.h>

using namespace std;

int main()
{
  string s;
  cin >> s;

  int freq[256] = {0};
  for (auto c : s) {
    freq[c]++;
  }
  sort(freq+'a', freq+'z'+1);
  cout << accumulate(freq+'a', freq+'z'+1-2, 0) << endl;
  

  return 0;
}
