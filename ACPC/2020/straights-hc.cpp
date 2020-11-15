#include <bits/stdc++.h>

using namespace std;

int main()
{
  int freq[10001] = {0};
  int N;
  cin >> N;
  for (int i = 0; i < N; i++) {
    int c;
    cin >> c;
    freq[c]++;
  }
  
  int ans = 0;
  for (int i = 1; i <= 10000; i++) {
    ans += max(0, freq[i] - freq[i-1]);
  }
  cout << ans << endl;
  return 0;
}
