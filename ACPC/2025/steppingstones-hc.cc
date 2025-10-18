#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> pii;

int N, M;
vector<vector<int>> h;

void solve()
{
  const int dr[] = { -1, 1, 0, 0 };
  const int dc[] = { 0, 0, -1, 1 };

  queue<pii> q;
  vector<vector<int>> dist(N, vector<int>(M, -1));

  for (int c = 0; c < M; c++) {
    q.emplace(0, c);
    dist[0][c] = 1;
  }

  while (!q.empty()) {
    auto [curr_r, curr_c] = q.front();
    q.pop();

    for (int d = 0; d < 4; d++) {
      int r2 = curr_r + h[curr_r][curr_c] * dr[d];
      int c2 = curr_c + h[curr_r][curr_c] * dc[d];

      if (r2 >= N) {
	cout << dist[curr_r][curr_c]+1 << endl;
	return;
      }

      if (0 <= r2 && r2 < N && 0 <= c2 && c2 < M && dist[r2][c2] == -1) {
	q.emplace(r2, c2);
	dist[r2][c2] = dist[curr_r][curr_c] + 1;
      }
    }
  }

  cout << -1 << endl;
}


int main()
{
  cin >> N >> M;
  h.resize(N, vector<int>(M));

  for (int r = 0; r < N; r++) {
    for (int c = 0; c < M; c++) {
      cin >> h[r][c];
    }
  }

  solve();

  return 0;
}
