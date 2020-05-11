/* @JUDGE_ID: 1102NT 149 C++ "" */

#include <iostream>
#include <cmath>
#include <list>
#include <cassert>

using namespace std;

const double pi = atan(1.0)*4;
const double minangle = pi/180.0 * 0.01;
const double EPSILON = minangle;

struct Range {
  double low, high;
  Range(double l, double h) { low = l; high = h; }
  bool operator<(const Range &r)
  {
    return low < r.low || (low == r.low && high < r.high);
  }
};

bool visible(const list<Range> &blocked, Range r)
{
  list<Range>::const_iterator p;
  for (p = blocked.begin(); p != blocked.end(); p++) {
    if (!(p->low > r.high || p->high < r.low)) {
      return false;
    }
  }
  return true;
}

void merge(list<Range> &blocked, Range r)
{
  list<Range>::iterator p, q;
  
  // not the most efficient merge, but should be fast enough because
  // the lists should be short
  blocked.push_back(r);
  blocked.sort();

  p = blocked.begin();
  while (p != blocked.end()) {
    while (true) {
      q = p;
      if (++q == blocked.end()) {
	break;    // no successor
      }
      if (q->low > p->high + EPSILON) {
	break;    // disjoint
      }
      if (q->high < p->high) {
	blocked.erase(q);    // q is contained in p
      } else {
	p->high = q->high;   // merge the two blocks
	blocked.erase(q);
      }
    }
    p++;
  }
}

// count visible trees above and to the right
//
// note: there won't be any trees directly above or to the right, because
//       xo and yo are not integers
int count_trees(double diameter, double xo, double yo)
{
  int trees = 0;
  list<Range> blocked;
  
  // s = sum of x and y coordinates of the tree we are looking at

  // this is cheating: we should go until 2*delta < minangle, but that
  // runs too long.  But choosing s < 40 gives the correct answer in
  // the amount of time allowed.
  for (int s = 2; s < 40; s++) {
    for (int x = 1; x <= s-1; x++) {
      int y = s - x;
      double xx = x - xo, yy = y-yo;
      double d = sqrt(xx*xx + yy*yy);

      assert(xx > 0 && yy > 0);
      double theta = atan2(yy,xx);     // angle to center of tree
      double delta = asin(diameter/2/d);  // angle to tangent to tree

      Range t(theta-delta, theta+delta);
      if (delta*2 >= minangle && visible(blocked, t)) {
	trees++;
      }
      
      Range r(theta-delta-minangle, theta+delta+minangle);
      merge(blocked, r);
    }
  }

  return trees;
}

int main(void)
{
  double diameter, xo, yo;
  int c;

  while ((cin >> diameter >> xo >> yo) && 
	 (diameter > 0 || xo > 0 || yo > 0)) {
    // we are going to split the plane into four quadrants (with (xo,yo)
    // as origin), and count separately
    c = count_trees(diameter, xo, yo) + count_trees(diameter, yo, 1-xo) + 
      count_trees(diameter, 1-xo, 1-yo) + count_trees(diameter, 1-yo, xo);
    cout << c << endl;
  }
  return 0;
}
