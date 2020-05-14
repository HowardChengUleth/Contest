#include <bits/stdc++.h>

using namespace std;

//
// The fact that we want to minimizes the sums of distances means that we want
// to compute a shortest path tree.  If distances from root (capital) to
// vertex i is d_i, then we can compute d_i with BFS.  An edge a->b can be in
// the shortest path tree iff d[a]+1 = d[b].
//
// To build a shortest path tree, we go through the nodes in order of
// increasing distances.  Each node is added to the tree using one of the
// possible edges (see above) to its parent.  Every combination of these
// choices gives a different tree

const int MAX = 200000;
typedef pair<int,int> Edge;

int n, m, k;
Edge edge[MAX];
int d[MAX];

vector<int> G[MAX];

void bfs()
{
  queue<int> q;
  fill(d, d+n, MAX+1);

  d[0] = 0;
  q.push(0);

  while (!q.empty()) {
    int v = q.front();
    q.pop();

    for (auto w : G[v]) {
      if (d[v]+1 < d[w]) {
	d[w] = d[v]+1;
	q.push(w);
      }
    }
  }
}

// vector of edges that can be used as a parent to that node in shortest
// path tree
vector<int> parent[MAX];

void print(int v, bool choice[], long long &options)
{
  if (options == 0) return;
  if (v == n) {
    for (int i = 0; i < m; i++) {
      cout << (choice[i] ? 1 : 0);
    }
    cout << endl;
    options--;
    return;
  }

  for (auto e : parent[v]) {
    choice[e] = true;
    print(v+1, choice, options);
    choice[e] = false;
  }
}

int main()
{
  cin >> n >> m >> k;
  for (int i = 0; i < m; i++) {
    int a, b;
    cin >> a >> b;
    a--; b--;
    edge[i] = make_pair(a,b);
    G[a].push_back(b);
    G[b].push_back(a);
  }

  bfs();

  // now we go through all the edges to see which ones are useful
  for (int i = 0; i < m; i++) {
    auto [a,b] = edge[i];
    if (d[a]+1 == d[b]) {
      parent[b].push_back(i);
    }
    if (d[b]+1 == d[a]) {
      parent[a].push_back(i);
    }
  }

  // number of options is just the product of number of parents at each
  // node, but watch for overflow
  long long options = 1;
  for (int i = 1; i < n; i++) {
    options *= parent[i].size();
    if (options >= k) {
      options = k;
      break;
    }
  }
  cout << options << endl;

  // now we go through all combinations.  It is not actually that important
  // to do that in order of increasing distance because of the structure
  // of the shortest path tree
  bool choice[MAX] = {0};
  print(1, choice, options);


  return 0;
}
