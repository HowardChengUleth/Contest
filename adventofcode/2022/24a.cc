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

  Node(int T = 0, int R = 0, int C = 0)
    : t{T}, r{R}, c{C} { }
  
  bool operator<(const Node &n) const
  {
    if (t != n.t) return t < n.t;
    if (r != n.r) return r < n.r;
    return c < n.c;
  }

  bool is_start() const
  {
    return r == -1 && c == 0;
  }

  bool is_end() const
  {
    return r == H && c == W-1;
  }

  bool inside() const
  {
    if (is_start() || is_end()) return true;
    return (0 <= r && r < H && 0 <= c && c < W);
  }

  bool can_move() const
  {
    if (is_start() || is_end()) return true;
    
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

    const int dr[] = {0, -1, 1, 0, 0};
    const int dc[] = {0, 0, 0, -1, 1};

    for (int d = 0; d < 5; d++) {
      Node next = curr;
      next.t = (next.t + 1) % (H*W);
      next.r += dr[d];
      next.c += dc[d];
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
