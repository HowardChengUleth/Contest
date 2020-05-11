#include <iostream>
#include <algorithm>
#include <set>
#include <climits>
#include <cassert>

using namespace std;

typedef long long ll;

const int MAXN = 100000;

bool inserting;

struct Machine
{
  ll D, P, R, G;

  void read()
  {
    cin >> D >> P >> R >> G;
  }

  bool operator<(const Machine &m) const
  {
    return D < m.D;
  }
};

struct Line
{
  ll m, b;                   // y = mx+b
  long double left, right;

  Line(ll mm, ll bb, long double l, long double r): m(mm), b(bb), left(l), right(r) { }
  
  long double eval(long double x) const
  {
    return m*x+b;
  }
  
  bool operator==(const Line &L) const
  {
    if (inserting) {
      return m == L.m && b == L.b;
    } else {
      return left <= L.left && L.right <= right;
    }
  }

  bool operator<(const Line &L) const
  {
    if (inserting) {
      return (m != L.m) ? m < L.m : b < L.b;
    } else {
      return (right < L.left);
    }
  }

  long double intersect(const Line &L) const
  {
    assert(m != L.m);
    return (long double)(L.b - b) / (m - L.m);
  }
};

bool debug = false;

struct Hull
{
  set<Line> lines;
  typedef set<Line>::iterator LineIt;
  
  void add(Line line, ll x)
  {
    inserting = true;
    LineIt it = lines.lower_bound(line);

    // same line as another one, just ignore it
    if (it != lines.end() && *it == line) return;

    // get rid of all lines with higher slopes dominated by this line
    while (it != lines.end()) {
      if (line.eval(it->right) < it->eval(it->right)) {
	break;
      }
      LineIt it2 = it;  ++it2;
      lines.erase(it);
      it = it2;
    }

    // get rid of all lines with lower slopes dominated by this line
    while (it != lines.begin()) {
      --it;
      if (line.eval(it->left) < it->eval(it->left)) {
	break;
      }
      LineIt it2 = it; ++it2;
      lines.erase(it);
      it = it2;
    }

    // if this line is below the hull, exit
    it = lines.lower_bound(line);
    if (it != lines.end()) {
      if (it->m == line.m) {
	if (it->b > line.b) return;
      } else {
	long double x = line.intersect(*it);
	if (x < it->left) return;
      }
    }
    if (it != lines.begin()) {
      LineIt it2 = it; it2--;
      if (it2->m == line.m) {
	if (it2->b > line.b) return;
      } else {
	long double x = line.intersect(*it2);
	if (x > it2->right) return;
      }
    }
    
    // this line is in the hull
    it = lines.insert(line).first;
    
    // intersect before and after
    if (it != lines.begin()) {
      LineIt before = it;  before--;
      long double x = it->intersect(*before);
      *(const_cast<long double *>(&(it->left))) = x;
      *(const_cast<long double *>(&(before->right))) = x;
    }

    LineIt after = it;  ++after;
    if (after != lines.end()) {
      long double x = it->intersect(*after);
      *(const_cast<long double *>(&(it->right))) = x;
      *(const_cast<long double *>(&(after->left))) = x;
    }
  }

  ll max(ll x)
  {
    inserting = false;
    LineIt it = lines.find(Line(0, 0, x, x));
    return it->eval(x);
  }
};

int N, C, D;
Machine mach[MAXN];

bool solve(int id)
{
  cin >> N >> C >> D;
  if (!N && !C && !D) return false;

  //  cout << N << ' ' << C << ' ' << D << endl;
  for (int i = 0; i < N; i++) {
    mach[i].read();
  }
  sort(mach, mach+N);

  Hull h;
  h.add(Line(0, C, 0, D), mach[0].D);

  for (int i = 0; i < N; i++) {
    // what is the max dollar we can have from the day before?
    ll avail = h.max(mach[i].D-1);
    //    cout << "i = " << i << ": avail = " << avail << endl;

    // not enough money to buy
    if (avail < mach[i].P) continue;

    ll b = avail - mach[i].P - mach[i].G * mach[i].D + mach[i].R;
    h.add(Line(mach[i].G, b, 0, D), (i < N-1) ? mach[i+1].D : D);
  }
  
  // sell the machine after day D
  cout << "Case " << id << ": " << h.max(D) << endl;
  
  return true;
}

int main()
{
  int id = 1;
  while (solve(id++))
    ;

  return 0;
}
