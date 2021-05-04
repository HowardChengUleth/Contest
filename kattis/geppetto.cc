#include <bits/stdc++.h>

using namespace std;

int main()
{
  int N, M;
  cin >> N >> M;

  pair<int,int> bad[400];
  for (int i = 0; i < M; i++) {
    cin >> bad[i].first >> bad[i].second;
  }

  int ans = 0;
  for (int S = 0; S < (1 << N); S++) {
    bool good = true;
    for (int i = 0; i < M && good; i++) {
      good &= !((S & (1 << (bad[i].first-1))) &&
		(S & (1 << (bad[i].second-1))));
    }
    if (good) {
      ans++;
    }
  }
  
  cout << ans << endl;

  return 0;
}
