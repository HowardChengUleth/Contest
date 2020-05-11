// We store the coordinates of the man and the box in each state, and
// figure out how to get from the start state to the goal state using
// BFS.  There are not that many states (20^4) so this is fast enough.
// Some care needs to be taken to determine the next states.

#include <iostream>
#include <string>
#include <algorithm>
#include <queue>
#include <map>

using namespace std;

int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

struct State
{
  pair<int, int> man, box;
  bool operator<(const State &s) const
  {
    if (man != s.man) return man < s.man;
    return box < s.box;
  }
  bool operator==(const State &s) const
  {
    return man == s.man && box == s.box;
  }
};

bool do_case()
{
  int n, m;
  cin >> n >> m;
  if (!n && !m) return false;

  State start, goal;
  char maze[20][20];
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> maze[i][j];
      switch (maze[i][j]) {
	case '@':
	  start.man = make_pair(i, j);
	  break;
	case 'd':
	  goal.man = make_pair(i, j);
	  break;
	case 'x':
	  start.box = make_pair(i, j);
	  break;
	case 'b':
	  goal.box = make_pair(i, j);
	  break;
      }
    }
  }

  map<State, int> dist;
  queue<State> q;
  dist[start] = 0;
  q.push(start);
  while (!q.empty()) {
    State curr = q.front();
    q.pop();
    int d = dist[curr];
    if (curr == goal) {
      cout << d << endl;
      return true;
    }
     
    for (int i = 0; i < 4; i++) {
      State next = curr;
      next.man.first += dr[i];
      next.man.second += dc[i];

      if (!(0 <= next.man.first && next.man.first < n &&
	    0 <= next.man.second && next.man.second < m)) continue;
      
      if (maze[next.man.first][next.man.second] == '#') continue;
      if (maze[next.man.first][next.man.second] == 'd' &&
	  curr.box != goal.box) continue;

      if (next.man == next.box) {
	// move the box too
	next.box.first += dr[i];
	next.box.second += dc[i];
      }
      if (!(0 <= next.box.first && next.box.first < n &&
	    0 <= next.box.second && next.box.second < m)) continue;
      if (maze[next.box.first][next.box.second] == '#') continue;
      if (maze[next.box.first][next.box.second] == 'd') continue;

      if (dist.find(next) == dist.end()) {
	dist[next] = d+1;
	q.push(next);
      }
    }
  }

  cout << "No Way!" << endl;
  
  return true;
}

int main(void)
{
  while (do_case())
    ;

  return 0;
}
