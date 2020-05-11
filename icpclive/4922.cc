// for each line, sort the points in that direction and break ties in
// the orthogonal direction.  Consecutive points on the same line are
// collisions.
//
// in fact, it is even faster just by hashing the lines.  If there are
// k queens on a line, then the number of collisions on that line is k-1.

#include <iostream>
#include <algorithm>

using namespace std;

typedef pair<int,int> pii;


pii queen[30000];
int num_q;

int selx(const pii &p)
{
  return p.first;
}

int sely(const pii &p)
{
  return p.second;
}

int seld1(const pii &p)
{
  return p.first + p.second;
}

int seld2(const pii &p)
{
  return p.first - p.second;
}

bool cmp1(const pii &p1, const pii &p2)
{
  int x1 = selx(p1), x2 = selx(p2);
  int y1 = sely(p1), y2 = sely(p2);

  if (x1 != x2) return x1 < x2;
  return y1 < y2;
}

bool cmp2(const pii &p1, const pii &p2)
{
  int x1 = sely(p1), x2 = sely(p2);
  int y1 = selx(p1), y2 = selx(p2);

  if (x1 != x2) return x1 < x2;
  return y1 < y2;
}

bool cmp3(const pii &p1, const pii &p2)
{
  int x1 = seld1(p1), x2 = seld1(p2);
  int y1 = seld2(p1), y2 = seld2(p2);

  if (x1 != x2) return x1 < x2;
  return y1 < y2;
}

bool cmp4(const pii &p1, const pii &p2)
{
  int x1 = seld2(p1), x2 = seld2(p2);
  int y1 = seld1(p1), y2 = seld1(p2);

  if (x1 != x2) return x1 < x2;
  return y1 < y2;
}

int count(pii queen[], int (*sel)(const pii &p))
{
  int ans = 0;
  for (int i = 0; i < num_q-1; i++) {
    if (sel(queen[i]) == sel(queen[i+1])) {
      ans++;
    }
  }
  return ans;
}

bool solve()
{
  int n, g;
  cin >> n >> g;
  if (!n) return false;

  num_q = 0;
  for (int i = 0; i < g; i++) {
    int k, x, y, s, t;
    cin >> k >> x >> y >> s >> t;
    while (k-- > 0) {
      queen[num_q++] = make_pair(x,y);
      x += s;
      y += t;
    }
  }

  int collisions = 0;
  sort(queen, queen+num_q, cmp1);
  collisions += count(queen, selx);

  sort(queen, queen+num_q, cmp2);
  collisions += count(queen, sely);
  
  sort(queen, queen+num_q, cmp3);
  collisions += count(queen, seld1);
  
  sort(queen, queen+num_q, cmp4);
  collisions += count(queen, seld2);

  cout << collisions << endl;
  return true;
}

int main(void)
{
  while (solve())
    ;
  return 0;
}
	
