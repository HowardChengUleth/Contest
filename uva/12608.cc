// Idea: straightforward, just do it.

#include <iostream>

using namespace std;

void solve()
{
  int W, N;
  cin >> W >> N;

  int x[1000], w[1000];
  for (int i = 0; i < N; i++) {
    cin >> x[i] >> w[i];
  }

  int dist = 0;
  int weight = 0;
  for (int i = 0; i < N; i++) {
    if (weight + w[i] > W) {
      dist += 2 * x[i];
      weight = 0;
    }
    weight += w[i];
    if (weight == W || i == N-1) {
      dist += 2 * x[i];
      weight = 0;
    }
  }

  
  cout << dist << endl;
}

int main()
{
  int T;
  cin >> T;
  while (T--) {
    solve();
  }
  return 0;
}
