#include <iostream>
#include <string>
#include <algorithm>
#include <queue>

using namespace std;

int w, h;
string grid[1000];
int burn_time[1000][1000];
int esc_time[1000][1000];

typedef pair<int,int> pii;
const int INF = 2000000;

const int dr[] = {-1, 1, 0, 0};
const int dc[] = {0, 0, -1, 1};

void get_burned()
{
  for (int r = 0; r < h; r++) {
    fill(burn_time[r], burn_time[r]+w, INF);
  }
  
  queue<pii> q;
  for (int r = 0; r < h; r++) {
    for (int c = 0; c < w; c++) {
      if (grid[r][c] == '*') {
	burn_time[r][c] = 0;
	q.push(pii(r,c));
      }
    }
  }

  while (!q.empty()) {
    pii curr = q.front();
    q.pop();

    for (int d = 0; d < 4; d++) {
      pii next = curr;
      next.first += dr[d];
      next.second += dc[d];
      if (!(0 <= next.first && next.first < h &&
	    0 <= next.second && next.second < w)) continue;
      if (grid[next.first][next.second] == '#') continue;
      if (burn_time[next.first][next.second] != INF) continue;

      burn_time[next.first][next.second] = burn_time[curr.first][curr.second]+1;
      q.push(next);
    }
  }
}

void escape()
{
  for (int r = 0; r < h; r++) {
    fill(esc_time[r], esc_time[r]+w, INF);
  }
  
  queue<pii> q;
  for (int r = 0; r < h; r++) {
    for (int c = 0; c < w; c++) {
      if (grid[r][c] == '@') {
	esc_time[r][c] = 0;
	q.push(pii(r,c));
      }
    }
  }

  while (!q.empty()) {
    pii curr = q.front();
    q.pop();

    if (curr.first == 0 || curr.first == h-1 ||
	curr.second == 0 || curr.second == w-1) {
      cout << esc_time[curr.first][curr.second]+1 << endl;
      return;
    }

    for (int d = 0; d < 4; d++) {
      pii next = curr;
      next.first += dr[d];
      next.second += dc[d];
      if (!(0 <= next.first && next.first < h &&
	    0 <= next.second && next.second < w)) continue;
      if (grid[next.first][next.second] == '#') continue;
      if (esc_time[next.first][next.second] != INF) continue;
      
      esc_time[next.first][next.second] = esc_time[curr.first][curr.second]+1;
      if (esc_time[next.first][next.second] >= burn_time[next.first][next.second]) continue;
      q.push(next);
    }
  }
  cout << "IMPOSSIBLE" << endl;
}

void solve()
{
  cin >> w >> h;
  for (int r = 0; r < h; r++) {
    cin >> grid[r];
  }

  get_burned();
  escape();
}

int main()
{
  int T;
  cin >> T;
  while (T--)
    solve();

  return 0;
}
