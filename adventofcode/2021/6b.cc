#include <bits/stdc++.h>

using namespace std;

int main()
{
  string line;
  cin >> line;
  replace(begin(line), end(line), ',', ' ');

  typedef long long ll;
  
  ll freq[9] = {0};
  int x;
  istringstream iss(line);
  while (iss >> x) {
    freq[x]++;
  }

  for (int i = 0; i < 256; i++) {
    ll freq2[9] = {0};

    freq2[6] += freq[0];
    freq2[8] += freq[0];
    for (int i = 1; i < 9; i++) {
      freq2[i-1] += freq[i];
    }
    
    copy(freq2, freq2+9, freq);
  }

  cout << accumulate(freq, freq+9, 0LL) << endl;
  
  return 0;
}
