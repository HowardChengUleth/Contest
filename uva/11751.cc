// note that the last vertex never has to be marked.
//
// we look at the vertices from largest to smallest.  If there is any
// edge from the current vertex to a larger uncovered vertex, then we
// must choose the current vertex.  Otherwise it is always better to
// defer (even if every smaller vertex has to be covered).  This is
// due to the property of binary arithmetic.

#include <iostream>
#include <algorithm>

using namespace std;

bool do_case()
{
  int n, m;
  cin >> n >> m;
  if (!n && !m) return false;

  int A[1000];
  fill(A, A+n, 0);
  pair<int,int> edges[25000];
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    if (u > v) swap(u, v);
    edges[i] = make_pair(u,v);
  }
  sort(edges, edges+m);
  for (int i = m-1; i >= 0; i--) {
    if (A[edges[i].first] || A[edges[i].second]) continue;
    A[edges[i].first] = 1;
  }

  for (int i = 0; i < n; i++) {
    cout << A[i];
  }
  cout << endl;

  return true;
}

int main(void)
{
  while (do_case()) 
    ;
  return 0;
}
