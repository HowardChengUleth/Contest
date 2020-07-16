#include <bits/stdc++.h>

using namespace std;

// if it is only operation 1 and 3, we can augment the usual union-find
// data structure to also keep track of how many elements and the sum of
// the elements for each set at the representative node.
//
// To handle move, whenever we move an element p we create a new element
// to represent the new p and initialize its union-find entry to be a
// singleton set, and merge it to the destination.  The sum and count of
// the original set containing p would be adjusted, but the old node for p
// is left in place so the find operation on the original set will still work.
// Notice that leaving this node in place would not affect the sum and count
// provided that they have been adjusted.

struct UnionFind
{
  vector<int> uf, count, index;
  vector<long long> sum;
  int next;
  UnionFind(int n, int m) :
    uf(n+m+1), count(n+m+1), index(n+1), sum(n+m+1), next(n+1)
  {
    for (int i = 0; i <= n; i++) {
      uf[i] = i;
      count[i] = 1;
      sum[i] = i;
      index[i] = i;
    }
    for (int i = n+1; i <= n+m; i++) {
      uf[i] = i;
      count[i] = 1;
      sum[i] = 0;
    }
  }

  int find(int x)
  {
    return find_helper(index[x]);
  }
  
  int find_helper(int x)
  {
    return (uf[x] == x) ? x : (uf[x] = find_helper(uf[x]));
  }
  
  bool merge(int x, int y)
  {
    int res1 = find(x), res2 = find(y);
    if (res1 == res2) return false;
    uf[res2] = res1;
    sum[res1] += sum[res2];
    count[res1] += count[res2];
    return true;
  }

  void move(int x, int y)
  {
    int res1 = find(x), res2 = find(y);
    if (res1 == res2) return;
    count[res1]--;
    sum[res1] -= x;
    index[x] = next;
    sum[next] = x;
    next++;
    merge(x, y);
  }
};

bool solve()
{
  int n, m;
  if (!(cin >> n >> m))
    return false;
  
  UnionFind uf(n, m);
  for (int i = 0; i < m; i++) {
    int c, p, q;
    cin >> c >> p;
    switch (c) {
    case 1:
      cin >> q;
      uf.merge(p, q);
      break;
    case 2:
      cin >> q;
      uf.move(p, q);
      break;
    case 3:
      q = uf.find(p);
      cout << uf.count[q] << ' ' << uf.sum[q] << endl;
    }
  }

  return true;
}

int main()
{
  while (solve())
    ;

  return 0;
}
