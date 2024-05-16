#include <bits/stdc++.h>

using namespace std;

int main()
{
  int freq[256] = {0};
  char ch;
  while (cin >> ch) {
    freq[ch]++;
  }

  int ans = 0;
  const string S = "TCG";
  int numset = INT_MAX;
  for (auto c : S) {
    ans += freq[c] * freq[c];
    numset = min(numset, freq[c]);
  }

  ans += numset * 7;
  cout << ans << endl;
  return 0;
}
