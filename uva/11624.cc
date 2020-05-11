#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

typedef pair<int, int> pii;

const int dr[] = { -1, 1, 0, 0 };
const int dc[] = { 0, 0, -1, 1 };

char A[1000][1000];
int joedist[1000][1000];
int firedist[1000][1000];

void solve()
{
  int R, C;
  cin >> R >> C;

  for (int i = 0; i < R; i++) {
    for (int j = 0; j < C; j++) {
      cin >> A[i][j];
    }
  }

  // now figure distance to fire
  queue<pii> q;
  for (int i = 0; i < R; i++) {
    for (int j = 0; j < C; j++) {
      firedist[i][j] = (A[i][j] == 'F') ? 0 : -1;
      if (A[i][j] == 'F') {
	q.push(make_pair(i, j));
      }
    }
  }
  
  while (!q.empty()) {
    pii curr = q.front();
    q.pop();

    for (int d = 0; d < 4; d++) {
      int ii = curr.first + dr[d], jj = curr.second + dc[d];
      if (!(0 <= ii && ii < R && 0 <= jj && jj < C)) continue;
      if (A[ii][jj] == '#') continue;
      if (firedist[ii][jj] >= 0) continue;
      firedist[ii][jj] = firedist[curr.first][curr.second] + 1;
      q.push(make_pair(ii, jj));
    }
  }

  // now move Joe
  for (int i = 0; i < R; i++) {
    for (int j = 0; j < C; j++) {
      joedist[i][j] = (A[i][j] == 'J') ? 0 : -1;
      if (A[i][j] == 'J') {
	q.push(make_pair(i, j));
      }
    }
  }

  while (!q.empty()) {
    pii curr = q.front();
    q.pop();
    if (curr.first == 0 || curr.first == R-1 || curr.second == 0 ||
	curr.second == C-1) {
      cout << joedist[curr.first][curr.second]+1 << endl;
      return;
    }
    for (int d = 0; d < 4; d++) {
      int ii = curr.first + dr[d], jj = curr.second + dc[d];
      if (!(0 <= ii && ii < R && 0 <= jj && jj < C)) continue;
      if (A[ii][jj] == '#') continue;
      if (joedist[ii][jj] >= 0) continue;
      int t = joedist[curr.first][curr.second] + 1;
      if (firedist[ii][jj] >= 0 && t >= firedist[ii][jj]) continue;
      joedist[ii][jj] = t;
      q.push(make_pair(ii, jj));
    }
  }
  
  cout << "IMPOSSIBLE" << endl;
}

int main()
{
  int n;
  cin >> n;
  //n = 1;
  while (n--)
    solve();
  return 0;
}
