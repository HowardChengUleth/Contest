#include <bits/stdc++.h>

using namespace std;

// if the diameter is d, then there must be a "backbone" of d+1 vertices
// on a line (and so n >= d+1).  Now we look at each of the internal vertices
// on the line and see how many more vertices we can attach to them (limited
// by the degree bound k).  But there is also a limit on how deep of a tree
// you can attach to them (dictated by the distance to either end).
//
// Every time you attach a vertex to one of these nodes, you decrease the
// available degree by 1.  But the new node added can be attached to k-1
// new vertices and the depth is reduced by 1.
//
// So basically we will just use a queue to keep track of where you can
// still attach something.  This is basically linear time.
//
// We do have to worry about the special case when k = 1.

typedef pair<int,int> pii;

struct Entry
{
  int v, k, d;
  Entry(int vv, int kk, int dd)
    : v{vv}, k{kk}, d{dd} { }
};

int main()
{
  int n, d, k;
  cin >> n >> d >> k;

  if (n < d+1 || (k == 1 && !(n == 2 && d == 1))) {
    cout << "NO" << endl;
    return 0;
  }

  vector<pii> ans;

  // build the backbone
  for (int i = 1; i <= d; i++) {
    ans.emplace_back(i, i+1);
  }

  queue<Entry> q;
  for (int i = 2; i <= d; i++) {
    if (k > 2) {
      q.emplace(i, k-2, min(i-1, d+1-i));
    }
  }

  int next = d+2;
  while (ans.size() < n-1) {
    if (q.empty()) {
      cout << "NO" << endl;
      return 0;
    }

    auto curr = q.front();
    q.pop();

    ans.emplace_back(curr.v, next);
    if (--curr.k) {
      q.push(curr);
    }

    if (curr.d > 1 && k > 1) {
      q.emplace(next, k-1, curr.d-1);
    }

    next++;
  }

  cout << "YES" << endl;
  for (auto p : ans) {
    cout << p.first << ' ' << p.second << endl;
  }
  
  return 0;
}
