#include <bits/stdc++.h>

using namespace std;

void get_freq(string s, int freq[])
{
  istringstream iss(s);
  char atom;
  int cnt;

  while (iss >> atom) {
    if (!(iss >> cnt)) {
      cnt = 1;
      iss.clear();
    }
    freq[atom] += cnt;
  }
}

int main()
{
  int freq[256] = {0};
  int freq2[256] = {0};
  
  string s;
  int k;
  cin >> s >> k;

  get_freq(s, freq);
  for (int i = 0; i < 256; i++) {
    freq[i] *= k;
  }

  cin >> s;
  get_freq(s, freq2);

  int ans = INT_MAX;
  for (int i = 0; i < 256; i++) {
    if (freq2[i] == 0) continue;
    ans = min(ans, freq[i] / freq2[i]);
  }

  cout << ans << endl;
  



}
