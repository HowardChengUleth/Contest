#include <bits/stdc++.h>

using namespace std;

int H, W;

set<int> Bleft[40], Bright[40], Bup[110], Bdown[110];

void read_input()
{
  string line;

  int r = 0;
  while (getline(cin, line)) {
    if (H) {
      for (int c = 0; c < (int)line.length()-2; c++) {
	switch (line[c+1]) {
	case '<':
	  Bleft[r].insert(c);
	  break;
	case '>':
	  Bright[r].insert(c);
	  break;
	case '^':
	  Bup[c].insert(r);
	  break;
	case 'v':
	  Bdown[c].insert(r);
	  break;
	}
      }
      r++;
    }
    H++;
    W = line.length()-2;
  }
  H -= 2;

  assert(Bup[0].empty() && Bdown[0].empty() &&
	 Bup[W-1].empty() && Bdown[W-1].empty());

  cout << "H = " << H << ", W = " << W << endl;
}

struct Node
{
  int t, r, c;
  int stage;

  Node(int T = 0, int R = 0, int C = 0)
    : t{T}, r{R}, c{C}, stage{0} { }
  
  bool operator<(const Node &n) const
  {
    if (stage != n.stage) return stage < n.stage;
    if (t != n.t) return t < n.t;
    if (r != n.r) return r < n.r;
    return c < n.c;
  }

  bool is_start_coord() const
  {
    return r == -1 && c == 0;
  }

  bool is_end_coord() const
  {
    return r == H && c == W-1;
  }

  bool is_end() const
  {
    return is_end_coord() && stage == 2;
  }

  bool inside() const
  {
    if (is_start_coord() || is_end_coord()) return true;
    return (0 <= r && r < H && 0 <= c && c < W);
  }

  void make_move(int dir)
  {
    const int dr[] = {0, -1, 1, 0, 0};
    const int dc[] = {0, 0, 0, -1, 1};

    t = (t + 1) % (H*W);
    r += dr[dir];
    c += dc[dir];

    if (stage == 0 && is_end_coord()) {
      stage++;
    } else if (stage == 1 && is_start_coord()) {
      stage++;
    }
  }
  
  bool can_move() const
  {
    if (is_start_coord() || is_end_coord()) return true;
    
    // see if any left blizzard reaches us
    if (Bleft[r].count((c + t) % W)) return false;

    // check right
    if (Bright[r].count(((c - t) % W + W) % W)) return false;

    // check up
    if (Bup[c].count((r+t) % H)) return false;

    // check down
    if (Bdown[c].count(((r - t) % H + H) % H)) return false;

    return true;
  }
  
};

int search()
{
  queue<Node> q;
  map<Node, int> dist;

  Node start(0, -1, 0);
  q.push(start);
  dist[start] = 0;

  while (!q.empty()) {
    Node curr = q.front();
    q.pop();

    if (curr.is_end()) {
      return dist[curr];
    }

    for (int d = 0; d < 5; d++) {
      Node next = curr;
      next.make_move(d);
      if (!next.inside()) continue;
      if (next.can_move() && dist.find(next) == dist.end()) {
	q.push(next);
	dist[next] = dist[curr]+1;
      }
    }
  }
  assert(false);
}


int main()
{
  read_input();
  int ans = search();

  cout << ans << endl;
  return 0;
}
