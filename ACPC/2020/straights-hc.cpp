// The trick here is to realize that we can just look at the frequency
// of each numbers.  Whenever freq[i] > freq[i-1], we must start another
// straight.  The number of straights you need to start is exactly
// freq[i] - freq[i-1].  If they are equal then all current straights
// can keep going.  If freq[i] < freq[i-1] then some of the current straights
// will be stopped.
//
//

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
