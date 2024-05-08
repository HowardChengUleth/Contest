#include <bits/stdc++.h>

using namespace std;

const double EPS = 1e-6;

struct Interval
{
  double left, right;

  Interval(int x, int r, int l, int w)
  {
    if (r <= w/2.0) {
      // can't cover anything, just move them far away
      left = right = l*10; 
    } else {
      double len = sqrt(pow(r, 2) - pow(w/2.0, 2));
      left = max(0.0, x - len);
      right = min(double(l), x + len);
    }
  }

  bool operator<(const Interval &I) const
  {
    if (fabs(left - I.left) < EPS) {
      return right > I.right;
    }
    return left < I.left;
  }
};

bool solve()
{
  int n, l, w;
  if (!(cin >> n >> l >> w)) {
    return false;
  }

  vector<Interval> sprinklers;
  for (int i = 0; i < n; i++) {
    int x, r;
    cin >> x >> r;
    sprinklers.emplace_back(x, r, l, w);
  }

  sort(begin(sprinklers), end(sprinklers));

  double covered = 0;    // how far have we covered
  double can_cover = 0;  // how far we could cover
  int num = 0;
  bool gap = false;
  for (auto s : sprinklers) {
    // look at all the intervals that can be used and find the one
    // that reaches furthest

    //    cout << "left, right = " << s.left << ", " << s.right << endl;

    if (s.left > l) continue;   // ignore invalid intervals
    
    if (s.left <= covered) {
      can_cover = max(can_cover, s.right);
    } else {
      // no other intervals can cover without a gap
      // so let's see what we have accumulated
      if (can_cover + EPS < covered) {
	gap = true;
	break;
      }
      num++;
      covered = can_cover;

      if (s.left <= covered) {
	can_cover = max(can_cover, s.right);
      } else {
	gap = true;
	break;
      }
    }
  }

  if (covered+EPS < l && can_cover+EPS >= l) {
    num++;
    covered = can_cover;
    gap = false;
  }
  
  if (covered+EPS < l || gap) {
    cout << -1 << endl;
  } else {
    cout << num << endl;
  }

  //  cout << "num = " << num << endl;
  //cout << "covered = " << covered << endl;
  //cout << "can_cover = " << can_cover << endl;
  
  return true;
}

int main()
{
  while (solve())
    ;

  return 0;
}
