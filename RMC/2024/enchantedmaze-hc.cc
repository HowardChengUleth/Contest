#include <bits/stdc++.h>

//#define SOLN 

using namespace std;

int R, C;
vector<string> grid;

void read_grid()
{
  cin >> R >> C;
  grid.resize(R);
  for (int r = 0; r < R; r++) {
    cin >> grid[r];
  }
}

const int NUM_OBS = 4;
const int dr[] = { -1, 1, 0, 0 };
const int dc[] = { 0, 0, -1, 1 };

struct State
{
  int r1, c1, r2, c2;
  bool pressed[NUM_OBS];

  State()
  {
    bool first = true;
    for (int r = 0; r < R; r++) {
      for (int c = 0; c < C; c++) {
	if (grid[r][c] == 'S') {
	  if (first) {
	    r1 = r;
	    c1 = c;
	    first = false;
	  } else {
	    r2 = r;
	    c2 = c;
	  }
	}
      }
    }
    for (int i = 0; i < NUM_OBS; i++) {
      pressed[i] = false;
    }
  }

  void print() const
  {
    cout << "(" << r1 << ", " << c1 << ") (" << r2 << ", " << c2 << ") ";
    for (int i = 0; i < NUM_OBS; i++) {
      cout << pressed[i];
    }
    cout << endl;
  }
  
  bool goal() const
  {
    return grid[r1][c1] == 'E' && grid[r2][c2] == 'E';
  }
  
  bool inside(int r, int c) const
  {
    return 0 <= r && r < R && 0 <= c && c < C;
  }

  bool is_blocked(int r, int c) const
  {
    if (grid[r][c] == '#') {
      return true;
    }

    if ('a' <= grid[r][c] && grid[r][c] < 'a' + NUM_OBS) {
      return pressed[grid[r][c] - 'a'];
    }
    if ('A' <= grid[r][c] && grid[r][c] < 'A' + NUM_OBS) {
      return !pressed[grid[r][c] - 'A'];
    }

    return false;
  }
  
  bool move_twin(int &r, int &c, int dir) const
  {
    int new_r = r + dr[dir];
    int new_c = c + dc[dir];
    if (!inside(new_r, new_c) || grid[new_r][new_c] == '*') {
      return false;
    }

    // check if twin is blocked
    if (is_blocked(new_r, new_c)) {
      return true;
    }

    r = new_r;
    c = new_c;
    return true;
  }

  void check_switch(int r, int c, int new_r, int new_c, bool switches[]) const
  {
    if (r == new_r && c == new_c) {
      // haven't moved, don't do anything
      return;
    }

    if (isdigit(grid[new_r][new_c])) {
      switches[grid[new_r][new_c] - '1'] = true;
    }
  }

  bool can_move(int dir) const
  {
    int new_r1 = r1, new_c1 = c1;
    int new_r2 = r2, new_c2 = c2;

    // move them if possible
    if (!move_twin(new_r1, new_c1, dir) || !move_twin(new_r2, new_c2, dir)) {
      return false;
    }

    // cannot be in same spot
    if (new_r1 == new_r2 && new_c1 == new_c2) {
      return false;
    }

    // check if we stepped on switches
    bool switches[NUM_OBS] = { false };
    check_switch(r1, c1, new_r1, new_c1, switches);
    check_switch(r2, c2, new_r2, new_c2, switches);

    for (int i = 0; i < NUM_OBS; i++) {
      if (!switches[i]) continue;

      // other twin stepped on obstacle
      if (grid[new_r1][new_c1] - 'A' == i ||
	  grid[new_r1][new_c1] - 'a' == i)
	return false;
      if (grid[new_r2][new_c2] - 'A' == i ||
	  grid[new_r2][new_c2] - 'a' == i)
	return false;
    }
    
    return true;
  }

  void move(int dir)
  {
    assert(can_move(dir));

    int new_r1 = r1, new_c1 = c1;
    int new_r2 = r2, new_c2 = c2;
    move_twin(new_r1, new_c1, dir);
    move_twin(new_r2, new_c2, dir);
    bool switches[NUM_OBS] = { false };
    check_switch(r1, c1, new_r1, new_c1, switches);
    check_switch(r2, c2, new_r2, new_c2, switches);

    r1 = new_r1;
    c1 = new_c1;
    r2 = new_r2;
    c2 = new_c2;
    for (int i = 0; i < NUM_OBS; i++) {
      if (switches[i]) {
	pressed[i] = !pressed[i];
      }
    }
  }
    
  int hash() const
  {
    int val = r1;
    val = val * 10 + r2;
    val = val * 10 + c1;
    val = val * 10 + c2;
    for (int i = 0; i < NUM_OBS; i++) {
      val = val * 2 + (pressed[i] ? 1 : 0);
    }
    return val;
  }

  bool operator<(const State &s) const
  {
    return hash() < s.hash();
  }
};

void BFS()
{
  queue<State> Q;
  map<State, int> dist;
#ifdef SOLN
  map<State, pair<State, int>> pred;
#endif
  
  State start;
  dist[start] = 0;
  Q.push(start);
  
  while (!Q.empty()) {
    auto curr = Q.front();
    Q.pop();
    
    if (curr.goal()) {
      cout << dist[curr] << endl;
#ifdef SOLN
      string move_str;
      const string move_dir = "UDLR";
      while (pred.find(curr) != pred.end()) {
	move_str += move_dir[pred[curr].second];
	curr = pred[curr].first;
      }
      reverse(begin(move_str), end(move_str));
      cout << move_str << endl;
#endif
      return;
    }

    for (int dir = 0; dir < 4; dir++) {
      if (!curr.can_move(dir)) continue;
      State next = curr;
      next.move(dir);
      if (dist.find(next) == dist.end()) {
	dist[next] = dist[curr] + 1;
	Q.push(next);
#ifdef SOLN
	pred[next] = make_pair(curr, dir);
#endif
      }
    }
  }

  cout << -1 << endl;
}


int main()
{
  read_grid();

  BFS();

  return 0;
}
