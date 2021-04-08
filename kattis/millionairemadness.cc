#include <bits/stdc++.h>

using namespace std;

const int dr[] = {-1, 1, 0, 0};
const int dc[] = {0, 0, -1, 1};

typedef tuple<int,int,int> pqnode;

int main()
{
  int M, N;
  cin >> M >> N;

  int h[1000][1000];
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      cin >> h[i][j];
    }
  }

  int ans[1000][1000];
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      ans[i][j] = -1;
    }
  }
  ans[0][0] = 0;

  priority_queue<pqnode> pq;
  pq.emplace(0,0,0);

  while (!pq.empty()) {
    int dist, i, j;
    tie(dist,i,j) = pq.top();
    pq.pop();

    if (-dist > ans[i][j]) continue;
    
    for (int d = 0; d < 4; d++) {
      int i2 = i + dr[d], j2 = j + dc[d];
      if (!(0 <= i2 && i2 < M && 0 <= j2 && j2 < N)) continue;
      int cost = max(ans[i][j], max(0, h[i2][j2] - h[i][j]));
      if (ans[i2][j2] < 0 || cost < ans[i2][j2]) {
	ans[i2][j2] = cost;
	pq.emplace(-cost, i2, j2);
      }
    }
  }

  cout << ans[M-1][N-1] << endl;
  return 0;
}
