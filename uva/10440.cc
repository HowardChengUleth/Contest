#include <iostream>
#include <algorithm>

using namespace std;

typedef pair<int,int> pii;

// best[i] = earliest (time,trips) to transport first i cars
pii best[1441];

void solve()
{
  int n, t, m;
  cin >> n >> t >> m;

  int arr[1441];
  for (int i = 1; i <= m; i++) {
    cin >> arr[i];
  }

  best[0] = make_pair(0,0);
  fill(best+1, best+m+1, make_pair(-1,-1));

  for (int i = 1; i <= m; i++) {
    // try taking j cars with the last trip
    for (int j = 1; j <= i && j <= n; j++) {
      int time = best[i-j].first;
      if (i-j > 0) time += t;
      time = max(time, arr[i]) + t;

      int trips = best[i-j].second + 1;
      if (best[i].first == -1 || time < best[i].first ||
	  (time == best[i].first && trips < best[i].second)) {
	best[i] = make_pair(time, trips);
      }
    }
  }
  cout << best[m].first << ' ' << best[m].second << endl;
}

int main()
{
  int c;
  cin >> c;
  while (c--) {
    solve();
  }
  return 0;
}
