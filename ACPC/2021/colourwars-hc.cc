#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main()
{
  int N;
  cin >> N;

  int freq[10001] = {0};
  for (int i = 0; i < N; i++) {
    int x;
    cin >> x;
    freq[x]++;
  }

  ll ans = 0;
  for (int i = 0; i <= 10000; i++) {
    if (!freq[i]) continue;
    ans += (freq[i] + i) / (i+1) * (i+1);
  }

  cout << ans << endl;

  return 0;
}
