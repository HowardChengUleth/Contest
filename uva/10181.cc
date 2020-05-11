#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <map>
#include <queue>
#include <vector>
#include <functional>

using namespace std;

struct State;
typedef pair<int, State> pis;

struct State 
{
  int grid[16];
  int br, bc;

  State(int g[16], int r, int c)
    : br(r), bc(c)
  {
    copy(g, g+16, grid);
  }

  State(const State &s)
  {
    copy(s.grid, s.grid+16, grid);
    br = s.br;
    bc = s.bc;
  }

  const State &operator=(const State &s)
  {
    copy(s.grid, s.grid+16, grid);
    br = s.br;
    bc = s.bc;
    return *this;
  }

  int taxicab() const
  {
    int total = 0;
    for (int i = 0; i < 16; i++) {
      if (!grid[i]) continue;
      int r = i / 4, c = i % 4;
      int nr = (grid[i]-1) / 4, nc = (grid[i]-1) % 4;
      total += abs(nr-r) + abs(nc-c);
    }
    return total;
  }

  bool isDone() const 
  {
    return taxicab() == 0;
  }

  bool operator<(const State &s) const
  {
    return lexicographical_compare(grid, grid+16, s.grid, s.grid+16);
  }

  pis node(int dist) const
  {
    return make_pair(dist+taxicab(), *this);
  }

  bool move(char d) {
    int nr = br, nc = bc;
    switch (d) {
    case 'L':
      if (nc-- == 0) {
	return false;
      }
      break;
    case 'R':
      if (nc++ == 3) {
	return false;
      }
      break;
    case 'U':
      if (nr-- == 0) {
	return false;
      }
      break;
    case 'D':
      if (nr++ == 3) {
	return false;
      }
      break;
    }
    swap(grid[nr*4+nc], grid[br*4+bc]);
    br = nr;
    bc = nc;
    return true;
  }
};

typedef priority_queue<pis, vector<pis>, greater<pis> > PQ;
typedef map<State, pair<int, char> > M;

void add_state(PQ &pq, M &move, char x, const State &curr, int dist)
{
  State next = curr;

  if (next.move(x) && move.find(next) == move.end()) {
    pis next_node = next.node(dist);
    pq.push(next_node);
    move[next] = make_pair(dist, x);
  }
}

void print_path(const State &s, M &move)
{
  if (move[s].second == '*') return;
  State next = s;
  switch (move[s].second) {
  case 'L':
    next.move('R');
    break;
  case 'R':
    next.move('L');
    break;
  case 'U':
    next.move('D');
    break;
  case 'D':
    next.move('U');
    break;
  }
  print_path(next, move);
  cout << move[s].second;
}

void search(int grid[16], int blank_r, int blank_c)
{
  PQ pq;
  M move;

  State start_state(grid, blank_r, blank_c);
  pis start_node = start_state.node(0);
  move[start_state] = make_pair(0, '*');

  pq.push(start_node);
  while (!pq.empty()) {
    pis curr_node = pq.top();
    State curr_state = curr_node.second;
    pq.pop();

    if (curr_state.isDone()) {
      print_path(curr_state, move);
      cout << endl;
      return;
    }

    int dist = move[curr_state].first + 1;
    add_state(pq, move, 'L', curr_state, dist);
    add_state(pq, move, 'R', curr_state, dist);
    add_state(pq, move, 'U', curr_state, dist);
    add_state(pq, move, 'D', curr_state, dist);
  }

}

void solve()
{
  int grid[16];
  int blank_r, blank_c;
  for (int i = 0; i < 16; i++) {
    cin >> grid[i];
    if (grid[i] == 0) {
      blank_r = i / 4;
      blank_c = i % 4;
    }
  }

  int inv_sum = 0;
  for (int i = 0; i < 16; i++) {
    for (int j = i+1; j < 16; j++) {
      if (grid[i] && grid[j] && grid[i] > grid[j]) {
	inv_sum++;
      }
    }
  }

  if ((inv_sum + blank_r + 1) % 2 != 0) {
    cout << "This puzzle is not solvable." << endl;
  } else {
    search(grid, blank_r, blank_c);
  }
}

int main()
{
  int N;
  cin >> N;
  while (N--)
    solve();
  return 0;
}
