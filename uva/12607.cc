// Idea: Use BFS, the states are location, time (mod 4), and the subset of
// treasures collected so far.
#include <iostream>
#include <algorithm>
#include <queue>
#include <tr1/tuple>
#include <cassert>

using namespace std;
using namespace std::tr1;

// N = 0, E = 1, S = 2, W = 3
const string dirs = "NESW";
const int dr[4] = { -1, 0, 1, 0 };
const int dc[4] = { 0, 1, 0, -1 };

int dist[101][101][4][256];

int M, N;
int K;

struct State : tuple<int,int,int,int>
{
  State()
  {
    row() = col() = 1;
    time() = 0;
    subset() = 0;
  }
  
  int &row()
  {
    return get<0>(*this);
  }
  int &col()
  {
    return get<1>(*this);
  }
  int &time()
  {
    return get<2>(*this);
  }
  int &subset()
  {
    return get<3>(*this);
  }

  int row() const
  {
    return get<0>(*this);
  }
  int col() const
  {
    return get<1>(*this);
  }
  int time() const
  {
    return get<2>(*this);
  }
  int subset() const
  {
    return get<3>(*this);
  }

  bool is_goal() const
  {
    return row() == M && col() == N && subset() == (1 << K) - 1;
  }
};

bool solve()
{
  cin >> M >> N;
  if (!M && !N) return false;

  int door[101][101];
  int treasure[101][101];
  for (int r = 1; r <= M; r++) {
    for (int c = 1; c <= N; c++) {
      char ch;
      cin >> ch;
      door[r][c] = dirs.find(ch);
      treasure[r][c] = -1;
      for (int d = 0; d < 4; d++) {
	fill(dist[r][c][d], dist[r][c][d]+256, -1);
      }
    }
  }

  cin >> K;
  for (int i = 0; i < K; i++) {
    int r, c;
    cin >> r >> c;
    treasure[r][c] = i;
  }

  State start;
  queue<State> q;

  q.push(start);
  dist[start.row()][start.col()][0][0] = 0;
  while (!q.empty()) {
    State s = q.front();
    q.pop();

    int d = dist[s.row()][s.col()][s.time()][s.subset()];
    if (s.is_goal()) {
      cout << d << endl;
      return true;
    }

    // we can try not moving
    State next = s;
    next.time() = (s.time() + 1) % 4;
    if (dist[next.row()][next.col()][next.time()][next.subset()] == -1) {
      q.push(next);
      dist[next.row()][next.col()][next.time()][next.subset()] = d+1;
    }

    // we can try to move
    next = s;
    int dir = (door[s.row()][s.col()] + s.time()) % 4;
    next.row() = s.row() + dr[dir];
    next.col() = s.col() + dc[dir];
    if (!(1 <= next.row() && next.row() <= M &&
	  1 <= next.col() && next.col() <= N)) continue;
    next.time() = (s.time() + 1) % 4;
    if (treasure[next.row()][next.col()] >= 0) {
      next.subset() |= (1 << treasure[next.row()][next.col()]);
    }
    if (dist[next.row()][next.col()][next.time()][next.subset()] == -1) {
      q.push(next);
      dist[next.row()][next.col()][next.time()][next.subset()] = d+1;
    }
  }

  // should always have solution
  assert(false);
  return true;
}

int main()
{
  while (solve())
    ;
  
  return 0;
}
