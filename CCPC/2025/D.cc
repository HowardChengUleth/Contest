#include <bits/stdc++.h>

using namespace std;

const int dx[] = { -1, -1, -1, 0, 1, 1, 1, 0 };
const int dy[] = { -1, 0, 1, 1, 1, 0, -1, -1 };

int curr[100][100];

int r, c, x, y;
const int INF = INT_MAX;

bool inside(int xx, int yy)
{
  return 0 <= xx && xx < r && 0 <= yy && yy < c &&
    curr[xx][yy] >= 0;
}

int cost(int curr_dir, int move_dir)
{
  if (curr_dir == move_dir) return 0;
  if ((curr_dir+1) % 8 == move_dir) return 1;
  if ((move_dir+1) % 8 == curr_dir) return 1;
  return INF;
}

typedef pair<int,int> pii;
typedef pair<int,pii> pqelem;

int dijkstra(int sx, int sy)
{
  int dist[100][100];
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      dist[i][j] = -1;
    }
  }
  dist[sx][sy] = 0;

  priority_queue<pqelem, vector<pqelem>, greater<pqelem>> PQ;
  PQ.emplace(0, make_pair(sx, sy));

  while (!PQ.empty()) {
    auto [d, coord] = PQ.top();
    auto [xx, yy] = coord;
    PQ.pop();
    /*
    cout << "popping " << xx << ", " << yy << ", dist = " << d
	 << ", " << dist[xx][yy] << endl;
    */
    if (d > dist[xx][yy]) continue;
    //cout << " here" << endl;
    
    for (int dir = 0; dir < 8; dir++) {
      int x2 = xx + dx[dir], y2 = yy + dy[dir];
      if (!inside(x2, y2)) continue;
      int c = cost(curr[xx][yy], dir);
      if (c == INF) continue;
      c += d;
      if (dist[x2][y2] == -1 ||
	  c < dist[x2][y2]) {
	PQ.emplace(c, make_pair(x2, y2));
	dist[x2][y2] = c;
	//cout << "pushing " << x2 << ", " << y2 << ", dist = " << c << endl;
      }
    }
  }

  return dist[x][y];
}

int main()
{
  cin >> r >> c >> x >> y;
  x--; y--;
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      char ch;
      cin >> ch;
      if (ch == '#') {
	curr[i][j] = -1;
      } else {
	curr[i][j] = ch - '1';
      }
    }
  }
  /*
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      cout << setw(2) << curr[i][j]+1;
    }
    cout << endl;
  }
  */
  int best = INF;
  for (int dir = 0; dir < 8; dir++) {
    int x2 = x + dx[dir], y2 = y + dy[dir];
    if (!inside(x2, y2)) continue;
    int c = cost(curr[x][y], dir);
    if (c == INF) continue;
    /*
    cout << "curr[x][y] = " << curr[x][y]+1 << endl;
    cout << "  x2, y2 = " << x2 << ", " << y2 << endl;
    cout << "  dir = " << dir+1 << ", c = " << c;
    */
    int cost = dijkstra(x2, y2);
    if (cost < 0) continue;
    cost += c;
    
    //cout << ", cost = " << cost << endl;
    best = min(best, cost);
  }

  cout << best << endl;
	 
  return 0;
}
