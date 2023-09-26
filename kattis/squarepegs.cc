#include <bits/stdc++.h>

using namespace std;

int main()
{
  int N, M, K;
  cin >> N >> M >> K;

  vector<int> plot(N);
  for (int i = 0; i < N; i++) {
    int r;
    cin >> r;
    plot[i] = 4*r*r;
  }

  vector<int> house;
  for (int i = 0; i < M; i++) {
    int r;
    cin >> r;
    house.push_back(4*r*r);
  }
  for (int i = 0; i < K; i++) {
    int s;
    cin >> s;
    house.push_back(2*s*s);
  }

  sort(begin(plot), end(plot));
  sort(begin(house), end(house));

  int ans = 0;
  int plot_i = 0;
  for (auto h : house) {
    while (plot_i < plot.size() && plot[plot_i] <= h)
      plot_i++;
    if (plot_i < plot.size()) {
      ans++;
      plot_i++;
    }
  }

  cout << ans << endl;
  
  return 0;
}
