#include <bits/stdc++.h>

using namespace std;

int main()
{
  map<int,int> freq[2];

  int n;
  cin >> n;

  freq[1][0]++;
  
  int ps = 0;
  for (int i = 0; i < n; i++) {
    int a;
    cin >> a;
    ps ^= a;
    freq[i%2][ps]++;
  }

  long long ans = 0;
  for (int i = 0; i < 2; i++) {
    for (auto p : freq[i]) {
      ans += (long long)p.second * (p.second-1)/2;
    }
  }

  cout << ans << endl;
  return 0;
}
