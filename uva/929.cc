// idea: use Dijkstra's algorithm, except that O(n log n + m) is not fast
// enough for this problem.
//
// Instead, we use the fact that all edge weights have 0-9 to implement a
// better way to get the next closest node in the fringe.
//
// We use 10 queues, indexed by the distance of the node mod 10.  Since the
// edge weights are <= 9, if we go through the queues in circular order and
// add the next fringe vertices, we cannot "wraparound".  That is, if the
// current node is d = distance mod 10 away, then its neigbhours must be
// less than d + 10 away: so simply adding the neighbours to the appropriate
// queue and progressing through the queues in circular order will ensure that
// we go through the fringe vertices that are closest first.

#include <iostream>
#include <algorithm>
#include <cassert>
#include <queue>

using namespace std;

const int dr[4] = {-1, 1, 0, 0};
const int dc[4] = {0, 0, -1, 1};

bool visited[1000][1000];
int dist[1000][1000];
int grid[1000][1000];

void solve()
{
  int rows, cols;
  cin >> rows >> cols;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      cin >> grid[i][j];
    }
  }

  for (int i = 0; i < rows; i++) {
    fill(visited[i], visited[i]+cols, false);
    fill(dist[i], dist[i]+cols, -1);
  }

  queue< pair<int, int> > q[10];

  int q_index = 0;
  dist[0][0] = grid[0][0];
  visited[0][0] = true;
  q[grid[0][0]].push(make_pair(0, 0));
  while (true) {
    int count = 0;
    while (count < 10 && q[q_index].empty()) {
      q_index++;
      if (q_index == 10) q_index = 0;
      count++;
    }
    assert(count < 10);
    
    pair<int,int> curr = q[q_index].front();
    q[q_index].pop();

    if (curr == make_pair(rows-1, cols-1)) {
      cout << dist[rows-1][cols-1] << endl;
      return;
    }

    for (int i = 0; i < 4; i++) {
      int r = curr.first + dr[i];
      int c = curr.second + dc[i];
      if (0 <= r && r < rows && 0 <= c && c < cols) {
	int w = dist[curr.first][curr.second] + grid[r][c];
	if (dist[r][c] < 0 || w < dist[r][c]) {
	  dist[r][c] = w;
	  if (!visited[r][c]) {
	    q[w % 10].push(make_pair(r,c));
	  }
	}
      }
    }
  }
}

int main(void)
{
  int N;
  cin >> N;
  while (N-- > 0) {
    solve();
  }
  return 0;
}
