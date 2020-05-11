#include <iostream>

using namespace std;

void solve()
{
  int N, D;
  cin >> N >> D;

  int stones[200];
  int num = 0;
  stones[num++] = 0;
  stones[num++] = 0;
  while (N--) {
    char type, dummy;
    int M;
    cin >> type >> dummy >> M;
    stones[num++] = M;

    // double the big stones (so they will be used either way)
    if (type == 'B') {
      stones[num++] = M;
    }
  }
  stones[num++] = D;
  stones[num++] = D;

  int dist = 0;
  for (int i = 0; i+2 < num; i++) {
    dist = max(dist, stones[i+2] - stones[i]);
  }
  cout << dist << endl;
}

int main(void)
{
  int T;
  cin >> T;
  for (int i = 1; i <= T; i++) {
    cout << "Case " << i << ": ";
    solve();
  }

  return 0;
}
