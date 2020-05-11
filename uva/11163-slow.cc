#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <tr1/unordered_map>
#include <queue>
#include <vector>
#include <functional>

using namespace std;
using namespace std::tr1;

int taxicab_dist[40][40];

void init_taxicab()
{
  for (int i = 0; i < 40; i++) {
    for (int j = 0; j < 40; j++) {
      if (i != j) taxicab_dist[i][j] = 100000;
    }
  }

  for (int i = 0; i < 40; i++) {
    if (i-4 >= 0) {
      taxicab_dist[i][i-4] = taxicab_dist[i-4][i] = 1;
    }
    if (i+4 < 40) {
      taxicab_dist[i][i+4] = taxicab_dist[i+4][i] = 1;
    }
    int r = i/4;
    int nc = (i+1)%4;
    int ni = r*4+nc;
    taxicab_dist[i][ni] = taxicab_dist[ni][i] = 1;

    nc = (i+3)%4;
    ni = r*4+nc;
    taxicab_dist[i][ni] = taxicab_dist[ni][i] = 1;
  }

  for (int k = 0; k < 40; k++) {
    for (int i = 0; i < 40; i++) {
      for (int j = 0; j < 40; j++) {
	taxicab_dist[i][j] = min(taxicab_dist[i][k] + taxicab_dist[k][j],
				 taxicab_dist[i][j]);
      }
    }
  }
}

struct State;
typedef pair<int, State> pis;

struct State 
{
  int grid[40];
  int kr, kc;
  int rows;
  int tdist;

  State(int g[16], int r, int c, int num_rows)
    : kr(r), kc(c), rows(num_rows)
  {
    copy(g, g+(4*rows), grid);
    compute_taxicab();
  }

  State(const State &s)
  {
    copy(s.grid, s.grid+(4*s.rows), grid);
    kr = s.kr;
    kc = s.kc;
    rows = s.rows;
    tdist = s.tdist;
  }

  const State &operator=(const State &s)
  {
    copy(s.grid, s.grid+(4*s.rows), grid);
    kr = s.kr;
    kc = s.kc;
    rows = s.rows;
    tdist = s.tdist;
    return *this;
  }

  bool operator==(const State &s) const
  {
    return equal(grid, grid+4*rows-1, s.grid);
  }

  bool operator<(const State &s) const
  {
    return lexicographical_compare(grid, grid+4*rows-1, s.grid, s.grid+4*rows-1);
  }

  void compute_taxicab()
  {
    tdist = 0;
    for (int i = 0; i < 4*rows; i++) {
      if (!grid[i]) continue;
      tdist += taxicab_dist[i][grid[i]];
    }
  }

  bool isDone() const 
  {
    return tdist == 0;
  }

  pis node(int dist) const
  {
    return make_pair(dist+tdist, *this);
  }

  bool move(char d) {
    int nr = kr, nc = kc;
    switch (d) {
    case 'L':
      if (nc-- == 0) {
	nc = 3;
      }
      break;
    case 'R':
      if (nc++ == 3) {
	nc = 0;
      }
      break;
    case 'U':
      if (nr-- == 0) {
	return false;
      }
      break;
    case 'D':
      if (nr++ == rows-1) {
	return false;
      }
      break;
    }

    int ni = (nr << 2) | nc;
    int ki = (kr << 2) | kc;
    tdist += taxicab_dist[ki][grid[ni]] - taxicab_dist[ni][grid[ni]];
    swap(grid[ni], grid[ki]);
    kr = nr;
    kc = nc;
    return true;
  }
};

struct StateHash
{
  long operator() (const State &s) const
  {
    long val = 0;
    for (int i = 0; i < s.rows*4; i++) {
      val *= 40;
      val += s.grid[i];
    }
    return val;
  }
};

struct StateEqual
{						
  bool operator() (const State &s1, const State &s2) const
  {
    return s1 == s2;
  }
};

typedef priority_queue<pis, vector<pis>, greater<pis> > PQ;
typedef unordered_map<State, pair<int, char>, StateHash, StateEqual> M;

void add_state(PQ &pq, M &dist, char x, const State &curr, int new_dist)
{
  State next = curr;

  if (!next.move(x)) return;

  if (dist.insert(make_pair(next, make_pair(new_dist, x))).second) {
    pis next_node = next.node(new_dist);
    pq.push(next_node);
  }
}

void search(int grid[40], int N, int kr, int kc)
{
  PQ pq;
  M dist;

  State start_state(grid, kr, kc, N/4);
  pis start_node = start_state.node(0);
  dist[start_state] = make_pair(0, 'x');

  pq.push(start_node);
  while (!pq.empty()) {
    pis curr_node = pq.top();
    State curr_state = curr_node.second;
    pq.pop();

    if (curr_state.isDone()) {
      cout << dist[curr_state].first << endl;
      return;
    }

    int new_dist = dist[curr_state].first+1;
    char from = dist[curr_state].second;
    
    switch (from) {
    case 'R':
      add_state(pq, dist, 'R', curr_state, new_dist);
      add_state(pq, dist, 'U', curr_state, new_dist);
      add_state(pq, dist, 'D', curr_state, new_dist);
      break;
    case 'L':
      add_state(pq, dist, 'L', curr_state, new_dist);
      add_state(pq, dist, 'U', curr_state, new_dist);
      add_state(pq, dist, 'D', curr_state, new_dist);
      break;
    case 'U':
      add_state(pq, dist, 'R', curr_state, new_dist);
      add_state(pq, dist, 'L', curr_state, new_dist);
      add_state(pq, dist, 'U', curr_state, new_dist);
      break;
    case 'D':
      add_state(pq, dist, 'R', curr_state, new_dist);
      add_state(pq, dist, 'L', curr_state, new_dist);
      add_state(pq, dist, 'D', curr_state, new_dist);
      break;
    case 'x':
      add_state(pq, dist, 'R', curr_state, new_dist);
      add_state(pq, dist, 'L', curr_state, new_dist);
      add_state(pq, dist, 'U', curr_state, new_dist);
      add_state(pq, dist, 'D', curr_state, new_dist);
      break;
    }
  }
}

bool solve(int id)
{
  int grid[40];
  int kr, kc;
  int N;

  cin >> N;
  if (!N) return false;
  for (int i = 0; i < N; i++) {
    cin >> grid[i];
    if (--grid[i] == 0) {
      kr = i / 4;
      kc = i % 4;
    }
  }

  cout << "Set " << id << ":" << endl;
  search(grid, N, kr, kc);
  return true;
}

int main()
{
  init_taxicab();
  int id = 1;
  while (solve(id++))
    ;
  return 0;
}
