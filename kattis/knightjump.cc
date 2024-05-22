#include <bits/stdc++.h>

using namespace std;

const int dr[8] = { 2, 2, -2, -2, 1, 1, -1, -1 };
const int dc[8] = { 1, -1, 1, -1, 2, -2, 2, -2 };

string G[100];
int N;
int sr, sc;

bool inside(int r, int c)
{
  return (0 <= r && r < N && 0 <= c && c < N);
}

typedef pair<int,int> pii;

void BFS()
{
  int D[100][100];
  for (int r = 0; r < N; r++) {
    for (int c = 0; c < N; c++) {
      D[r][c] = -1;
    }
  }

  queue<pii> Q;
  Q.emplace(sr, sc);
  D[sr][sc] = 0;

  while (!Q.empty()) {
    auto [r, c] = Q.front();
    Q.pop();
    if (r == 0 && c == 0) {
      cout << D[r][c] << endl;
      return;
    }

    for (int d = 0; d < 8; d++) {
      int r2 = r + dr[d], c2 = c + dc[d];
      if (!inside(r2, c2) || G[r2][c2] == '#') continue;
      if (D[r2][c2] >= 0) continue;
      D[r2][c2] = D[r][c] + 1;
      Q.emplace(r2, c2);
    }
    
  }
  cout << -1 << endl;
}

int main()
{
  cin >> N;

  
  for (int r = 0; r < N; r++) {
    cin >> G[r];
    for (int c = 0; c < N; c++) {
      if (G[r][c] == 'K') {
	sr = r;
	sc = c;
      }
    }
  }

  BFS();


  return 0;
}
