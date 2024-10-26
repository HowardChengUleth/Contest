#include <bits/stdc++.h>

using namespace std;

int n, m;
int b;
int h[100][100];

const int dr[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int dc[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

struct State
{
  int r, c, speed;

  State(int rr, int cc, int ss)
    : r{rr}, c{cc}, speed{ss} { }
  
  bool operator<(const State &s) const {
    return tuple<int,int,int>(r, c, speed) <
      tuple<int,int,int>(s.r, s.c, s.speed);
  }
};

double dist[100][100][2001];
bool boost[100][100][100][100];
int max_speed[100][100];

bool inside(State s)
{
  int r = s.r, c = s.c;
  return 0 <= r && r < n && 0 <= c && c < m;
}

void dijkstra()
{
  typedef pair<double, State> pds;
  
  State start(0, 0, 0);
  priority_queue<pds, vector<pds>, greater<pds>> PQ;
  PQ.emplace(0, start);
  dist[0][0][0] = 0.0;

  while (!PQ.empty()) {
    auto [d, curr] = PQ.top();
    PQ.pop();

    // we had been here earlier with a faster speed
    if (curr.speed < max_speed[curr.r][curr.c]) continue;
    max_speed[curr.r][curr.c] = curr.speed;

    if (dist[curr.r][curr.c][curr.speed] < d) continue;

    for (int dir = 0; dir < 8; dir++) {
      State next(curr.r + dr[dir], curr.c + dc[dir], 0);
      if (!inside(next)) continue;

      int speed = curr.speed;
      speed += h[curr.r][curr.c] - h[next.r][next.c];
      if (boost[curr.r][curr.c][next.r][next.c]) {
	speed *= 2;
      }
      speed = max(0, min(2000, speed));

      if (speed == 0) continue;

      double apart = (dr[dir] && dc[dir]) ? 150 : 100;
      double time = d + apart / speed;
      next.speed = speed;
      if (dist[next.r][next.c][speed] < 0 ||
	  time < dist[next.r][next.c][speed]) {
	PQ.emplace(time, next);
	dist[next.r][next.c][speed] = time;
      }
    }
  }
}

int main()
{
  cin >> n >> m;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> h[i][j];
    }
  }

  cin >> b;
  for (int i = 0; i < b; i++) {
    int r1, c1, r2, c2;
    cin >> r1 >> c1 >> r2 >> c2;
    boost[r1][c1][r2][c2] = true;
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      fill(dist[i][j], dist[i][j] + 2001, -1);
    }
  }
  
  dijkstra();

  double ans = DBL_MAX;
  for (int sp = 0; sp <= 2000; sp++) {
    if (dist[n-1][m-1][sp] >= 0) {
      ans = min(ans, dist[n-1][m-1][sp]);
    }
  }

  cout << fixed << setprecision(10) << ans << endl;
  
  return 0;
}
