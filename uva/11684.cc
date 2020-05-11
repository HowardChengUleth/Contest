#include <iostream>
#include <algorithm>
#include <cassert>
#include <cmath>

using namespace std;

typedef pair<int,int> pii;

int n, m;
pii stake[1000];
bool known[1000];
int num_known;

bool ccwcheck(int bx, int by, int cx, int cy)
{
  long long dx1 = bx, dy1 = by;
  long long dx2 = cx, dy2 = cy;

  return (dx1*dy2 > dx2*dy1);
}

bool distcheck(int bx, int by, int cx, int cy, int y)
{
  long long dx = cx - bx, dy = cy - by;
  return dx*dx + dy*dy == y;
}

struct Triangle
{
  int a, b, c, x, y, z;

  int unknown() const
  {
    int ans = 3;
    if (known[a]) ans--;
    if (known[b]) ans--;
    if (known[c]) ans--;
    return ans;
  }

  int shared(const Triangle &t) const
  {
    return (a == t.a) + (a == t.b) + (a == t.c) +
      (b == t.a) + (b == t.b) + (b == t.c) +
      (c == t.a) + (c == t.b) + (c == t.c);
  }

  void rotate()
  {
    int temp = a;
    a = b;
    b = c;
    c = temp;
    temp = x;
    x = y;
    y = z;
    z = temp;
  }
  
  void solve()
  {
    assert(unknown() == 1);
    
    // rotate so that a and b are known
    bool match = false;
    for (int i = 0; i < 3 && !match; i++) {
      if (known[a] && known[b]) {
	match = true;
	break;
      } else {
	rotate();
      }
    }
    assert(match);

    int ax = stake[a].first, ay = stake[a].second;
    int bx = stake[b].first, by = stake[b].second;
    
    // translate a to origin
    bx -= ax;   by -= ay;

    // try all possible cx and cy, not too bad?
    for (long long cx = 0; cx*cx <= z; cx++) {
      long long cy = (long long)floor(sqrt(z - cx*cx) + 0.5);
      if (cx*cx + cy*cy != z) continue;
      if (distcheck(bx, by, cx, cy, y) && ccwcheck(bx, by, cx, cy)) {
	stake[c].first = cx + ax;
	stake[c].second = cy + ay;
	known[c] = true;
	break;
      } else if (distcheck(bx, by, -cx, cy, y) &&
		 ccwcheck(bx, by, -cx, cy)) {
	stake[c].first = -cx + ax;
	stake[c].second = cy + ay;
	known[c] = true;
	break;
      } else if (distcheck(bx, by, cx, -cy, y) &&
		 ccwcheck(bx, by, cx, -cy)) {
	stake[c].first = cx + ax;
	stake[c].second = -cy + ay;
	known[c] = true;
	break;
      } else if (distcheck(bx, by, -cx, -cy, y) &&
		 ccwcheck(bx, by, -cx, -cy)) {
	stake[c].first = -cx + ax;
	stake[c].second = -cy + ay;
	known[c] = true;
	break;
      }
    }
    assert(unknown() == 0);
  }
};

istream &operator>>(istream &is, Triangle &t)
{
  is >> t.a >> t.b >> t.c >> t.x >> t.y >> t.z;
  t.a--; t.b--; t.c--;
  return is;
}

Triangle tri[1000];

void DFS(int root)
{
  if (num_known == m) return;

  for (int i = 0; i < n && num_known < m; i++) {
    if (!(tri[i].shared(tri[root]) == 2 && tri[i].unknown() == 1)) continue;
    tri[i].solve();
    num_known++;
    DFS(i);
  }
}

bool do_case()
{
  cin >> n >> m;
  if (!n && !m) return false;

  for (int i = 0; i < n; i++) {
    cin >> tri[i];
  }

  fill(known, known+m, false);
  stake[0] = make_pair(0, 0);
  stake[1] = make_pair(0, 1);
  stake[2] = make_pair(1, 0);
  known[0] = known[1] = known[2] = true;
  num_known = 3;

  int root = -1;
  for (int i = 0; i < n; i++) {
    if (tri[i].unknown() == 0) {
      root = i;
      break;
    }
  }
  assert(root >= 0);
  
  DFS(root);

  for (int i = 0; i < m; i++) {
    cout << stake[i].first << ' ' << stake[i].second << endl;
  }
  
  return true;
}

int main(void)
{
  while (do_case())
    ;

  return 0;
}
