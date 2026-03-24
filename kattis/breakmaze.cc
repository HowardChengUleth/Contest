#include <bits/stdc++.h>

using namespace std;

int N, M, S;

int A[100][100];

typedef tuple<int,int,int> ti3;

const int dr[] = { -1, 1, 0, 0 };
const int dc[] = { 0, 0, -1, 1 };

void BFS()
{

  vector<vector<vector<int>>> dist(N,
				   vector<vector<int>>(M,
						       vector<int>(S+1, -1)));
  queue<ti3> q;

  if (S >= A[0][0]) {
    int s2 = S - A[0][0];
    q.emplace(0, 0, s2);
    dist[0][0][s2] = 0;
  }

  while (!q.empty()) {
    auto [r, c, s] = q.front();
    q.pop();

    if (r == N-1 && c == M-1) {
      cout << dist[r][c][s] << endl;
      return;
    }
    
    for (int d = 0; d < 4; d++) {
      int r2 = r + dr[d], c2 = c + dc[d];
      if (0 <= r2 && r2 < N && 0 <= c2 && c2 < M) {
	int s2 = s - A[r2][c2];
	if (s2 >= 0 && dist[r2][c2][s2] == -1) {
	  q.emplace(r2, c2, s2);
	  dist[r2][c2][s2] = dist[r][c][s] + 1;
	}
      }
    }
  }

  cout << -1 << endl;
}

int main()
{
  cin >> N >> M >> S;
  for (int r = 0; r < N; r++) {
    for (int c = 0; c < M; c++) {
      cin >> A[r][c];
    }
  }

  BFS();


  return 0;
}
