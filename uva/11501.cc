#include <iostream>
#include <algorithm>
#include <queue>
#include <map>
#include <string>
#include <utility>

using namespace std;

bool is_stump(char c)
{
  return c == 'S' || c == 'B' || c == 'E';
}

struct State {
  int rows, cols;
  string grid;
  int log;
  int curr;

  State(const string &s, int r, int c)
    : rows(r), cols(c), grid(s), log(0)
  {
    for (int i = 0; i < rows*cols; i++) {
      if (grid[i] == 'B') {
	curr = i;
      }
    }
  }

  bool operator<(const State &s) const
  {
    if (curr != s.curr) return curr < s.curr;
    if (log != s.log) return log < s.log;
    return grid < s.grid;
  }
    
  bool end_reached() const
  {
    return grid[curr] == 'E';
  }

  bool walk_up(State &s) const
  {
    if (curr < cols) return false;    // first row
    if (grid[curr - cols] != '|') return false; // can't go up
    
    s = *this;
    s.curr = curr - cols;
    while (grid[s.curr] == '|') {
      s.curr -= cols;
    }
    return true;
  }

  bool walk_down(State &s) const
  {
    if (curr >= rows*cols-cols) return false;    // last row
    if (grid[curr + cols] != '|') return false; // can't go down
    
    s = *this;
    s.curr = curr + cols;
    while (grid[s.curr] == '|') {
      s.curr += cols;
    }
    return true;
  }

  bool walk_left(State &s) const
  {
    if (curr % cols == 0) return false;    // first col
    if (grid[curr - 1] != '-') return false; // can't go left
    
    s = *this;
    s.curr = curr - 1;
    while (grid[s.curr] == '-') {
      s.curr--;
    }
    return true;
  }

  bool walk_right(State &s) const
  {
    if (curr % cols == cols-1) return false;    // last col
    if (grid[curr + 1] != '-') return false; // can't go right
    
    s = *this;
    s.curr = curr + 1;
    while (grid[s.curr] == '-') {
      s.curr++;
    }
    return true;
  }

  // assumes that we can walk in the appropriate direction and s is 
  // the destination after we walk in that direction
  bool pick_up(State &s) const
  {
    if (log) return false;              // already has a log
    
    s.log = abs(curr - s.curr) / cols;
    s.curr = curr;
    for (int i = curr - cols; grid[i] == '|'; i -= cols) {
      s.grid[i] = '.';
    }
    return true;
  }

  bool pick_down(State &s) const
  {
    if (log) return false;              // already has a log
    
    s.log = abs(curr - s.curr) / cols;
    s.curr = curr;
    for (int i = curr + cols; grid[i] == '|'; i += cols) {
      s.grid[i] = '.';
    }
    return true;
  }

  bool pick_left(State &s) const
  {
    if (log) return false;              // already has a log
    
    s.log = abs(curr - s.curr);
    s.curr = curr;
    for (int i = curr-1; grid[i] == '-'; i--) {
      s.grid[i] = '.';
    }
    return true;
  }

  bool pick_right(State &s) const
  {
    if (log) return false;              // already has a log
    
    s.log = abs(curr - s.curr);
    s.curr = curr;
    for (int i = curr+1; grid[i] == '-'; i++) {
      s.grid[i] = '.';
    }
    return true;
  }
  
  bool put_up(State &s) const
  {
    if (!log) return false;             // not holding log
    int l = log;

    int c = curr-cols;
    for (int i = 0; i < l-1; i++) {
      if (c < 0 || grid[c] != '.') return false;
      c -= cols;
    }
    if (c < 0 || !is_stump(grid[c])) return false;
    
    s = *this;
    c = curr-cols;
    for (int i = 0; i < l-1; i++) {
      s.grid[c] = '|';
      c -= cols;
    }
    s.log = 0;
    
    return true;
  }

  bool put_down(State &s) const
  {
    if (!log) return false;             // not holding log
    int l = log;

    int c = curr+cols;
    for (int i = 0; i < l-1; i++) {
      if (c >= rows*cols || grid[c] != '.') return false;
      c += cols;
    }
    if (c >= rows*cols || !is_stump(grid[c])) return false;
    
    s = *this;
    c = curr+cols;
    for (int i = 0; i < l-1; i++) {
      s.grid[c] = '|';
      c += cols;
    }
    s.log = 0;
    
    return true;
  }

  bool put_left(State &s) const
  {
    if (!log) return false;             // not holding log
    if (curr % cols - log < 0) return false;   // too long
    int l = log;

    int c = curr-1;
    for (int i = 0; i < l-1; i++) {
      if (grid[c] != '.') return false;
      c--;
    }
    if (!is_stump(grid[c])) return false;
    
    s = *this;
    c = curr-1;
    for (int i = 0; i < l-1; i++) {
      s.grid[c] = '-';
      c--;
    }
    s.log = 0;

    return true;
  }

  bool put_right(State &s) const
  {
    if (!log) return false;             // not holding log
    if (curr % cols + log >= cols) return false;  // too long
    int l = log;

    int c = curr+1;
    for (int i = 0; i < l-1; i++) {
      if (grid[c] != '.') return false;
      c++;
    }
    if (!is_stump(grid[c])) return false;
    
    s = *this;
    c = curr+1;
    for (int i = 0; i < l-1; i++) {
      s.grid[c] = '-';
      c++;
    }
    s.log = 0;
    
    return true;
  }
};

ostream &operator<<(ostream &os, const State &s)
{
  int k = 0;
  for (int i = 0; i < s.rows; i++) {
    for (int j = 0; j < s.cols; j++) {
      if (s.curr == k) {
	os << '*';
      } else {
	os << s.grid[k];
      }
      k++;
    }
    os << endl;
  }
  os << "Log = " << s.log << endl;
  os << "================================" << endl;
  return os;
}

void explore(const State &s, map<State,int> &dist, queue<State> &q, int d)
{
  if (dist.find(s) == dist.end()) {
    dist[s] = d+1;
    q.push(s);
  }
}

int BFS(const string &grid, int r, int c)
{
  State start(grid, r, c);

  map<State,int> dist;
  queue<State> q;
  dist[start] = 0;
  q.push(start);

  while (!q.empty()) {
    State curr = q.front();
    q.pop();

    /*    
    cout << "Debug (distance = " << dist[curr] << "):" << endl << endl;
    cout << curr << endl;
    */

    // are we done?
    int d = dist[curr];
    if (curr.end_reached()) {
      return d;
    }
    
    // try walking
    State next = curr;
    if (curr.walk_up(next)) {
      explore(next, dist, q, d);
      if (curr.pick_up(next)) {
	explore(next, dist, q, d);
      }
    }
    if (curr.walk_down(next)) {
      explore(next, dist, q, d);
      if (curr.pick_down(next)) {
	explore(next, dist, q, d);
      }
    }
    if (curr.walk_left(next)) {
      explore(next, dist, q, d);
      if (curr.pick_left(next)) {
	explore(next, dist, q, d);
      }
    }
    if (curr.walk_right(next)) {
      explore(next, dist, q, d);
      if (curr.pick_right(next)) {
	explore(next, dist, q, d);
      }
    }

    if (curr.put_up(next)) {
      explore(next, dist, q, d);
    }
    if (curr.put_down(next)) {
      explore(next, dist, q, d);
    }
    if (curr.put_left(next)) {
      explore(next, dist, q, d);
    }
    if (curr.put_right(next)) {
      explore(next, dist, q, d);
    }
  }
  
  return 0;      // not found
}

void solve(void)
{
  int r, c;
  cin >> r >> c;

  string grid;

  for (int i = 0; i < r; i++) {
    string s;
    cin >> s;
    grid += s;
  }
  
  cout << BFS(grid, r, c) << endl;
}

int main(void)
{
  int T;
  cin >> T;
  while (T-- > 0) {
    solve();
  }
  return 0;
}
