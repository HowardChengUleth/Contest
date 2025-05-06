#include <bits/stdc++.h>

using namespace std;

int main()
{
  int N;
  cin >> N;

  map<int,int> freq;
  for (int i = 0; i < N; i++) {
    int x;
    cin >> x;
    freq[x]++;
  }

  int ans = 0;
  for (auto [v, f] : freq) {
    int group_size = v+1;
    ans += (f + (group_size-1))/group_size * group_size;
  }

  cout << ans << endl;
  
  return 0;
}
