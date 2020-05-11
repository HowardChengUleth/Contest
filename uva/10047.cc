#include <iostream>
#include <map>
#include <queue>
#include <algorithm>

using namespace std;

int dr[4] = { -1, 0, 1, 0 };
int dc[4] = {  0, -1, 0, 1 };

struct Node : public pair< pair<int, int>, pair<int, int> >
{
  Node(int r = 0, int c = 0, int dir = 0, int color = 0)
  {
    first = make_pair(r, c);
    second = make_pair(dir, color);
  }

  int r() const { return first.first; }
  int c() const { return first.second; }
  int dir() const { return second.first; }
  int color() const { return second.second; }

  bool matchxdir(const Node &n) const
  {
    return first == n.first && color() == n.color();
  }
};

void solve(int m, int n)
{
  char grid[27][27];
  for (int i = 0; i < 27; i++) {
    fill(grid[i], grid[i]+27, '#');
  }

  Node start, end;
  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= n; j++) {
      cin >> grid[i][j];
      if (grid[i][j] == 'S') {			
	start = Node(i, j, 0, 0);
      } else if (grid[i][j] == 'T') {
	end = Node(i, j, 0, 0);
      }
    }
  }

  map<Node, int> dist;
  queue<Node> q;
  dist[start] = 0;
  q.push(start);

  while (!q.empty()) {
    Node curr = q.front();
    q.pop();

    if (end.matchxdir(curr)) {
      cout << "minimum time = " << dist[curr] << " sec" << endl;
      return;
    }

    // try to move forward by one square
    int r = curr.r(), c = curr.c(), dir = curr.dir(), color = curr.color();
    if (grid[r+dr[dir]][c+dc[dir]] != '#') {
      Node next(r+dr[dir], c+dc[dir], dir, (color+1)%5);
      if (dist.find(next) == dist.end()) {
	dist[next] = dist[curr]+1;
	q.push(next);
      }
    }

    // try turning left/right
    Node next(r, c, (dir+1)%4, color);
    if (dist.find(next) == dist.end()) {
      dist[next] = dist[curr]+1;
      q.push(next);
    }
    next = Node(r, c, (dir+3)%4, color);
    if (dist.find(next) == dist.end()) {
      dist[next] = dist[curr]+1;
      q.push(next);
    }
  }

  cout << "destination not reachable" << endl;
}

int main(void)
{
  int case_num = 1;
  int m, n;
  while (cin >> m >> n && (m || n)) {
    if (case_num > 1) cout << endl;
    cout << "Case #" << case_num++ << endl;
    solve(m, n);
  }
  return 0;
}
