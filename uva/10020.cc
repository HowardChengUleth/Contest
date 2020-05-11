#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

struct Interval {
  double l, r;

  bool operator<(const Interval &ivl) const
  {
    if (l != ivl.l) {
      return l < ivl.l;
    } else {
      return r > ivl.r;
    }
  }
  
  void set(double left, double right) {
    l = left;
    r = right;
  }
};

ostream &operator<<(ostream &os, const Interval &ivl)
{
  return os << ivl.l << " " << ivl.r;
}

int M;
int n;
Interval interval[100000];
int soln[100000];
int soln_n;

int main(void)
{
  int cases;
  double l, r;

  cin >> cases;

  while (cases-- > 0) {
    cin >> M;
    n = 0;
    while (cin >> l >> r && max(fabs(l), fabs(r)) > 1e-6) {
      interval[n++].set(l, r);
    }
    sort(interval, interval+n);

    double curr = 0;
    int soln_n = 0;
    int index = 0;

    while (curr < M) {
      int best_index = -1;
      while (index < n && interval[index].l <= curr) {
	if (best_index == -1 || interval[best_index].r < interval[index].r) {
	  best_index = index;
	}
	index++;
      }
      if (best_index == -1 || interval[best_index].r < curr) {
	break;
      }
      curr = interval[best_index].r;
      soln[soln_n++] = best_index;
    }

    if (curr < M) {
      cout << "0" << endl;
    } else {
      cout << soln_n << endl;
      for (int i = 0; i < soln_n; i++) {
	cout << interval[soln[i]] << endl;
      }
    }

    if (cases) {
      cout << endl;
    }
    
  }

  return 0;
}
