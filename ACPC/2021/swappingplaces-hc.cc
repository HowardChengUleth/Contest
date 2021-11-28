#include <bits/stdc++.h>

using namespace std;

int n, m;
vector<int> G[1000];
int perm[1000];

int label[1000];         // node -> label
int node[1000];          // label -> node
int parent[1000];
int children[1000] = {0};
int comp[1000];

queue<int> leaf;

typedef pair<int,int> pii;
vector<pii> swaps;

void DFS(int r, int id, int par = -1)
{
  parent[r] = par;
  comp[r] = id;
  for (auto c : G[r]) {
    if (c != par && comp[c] == -1) {
      DFS(c, id, r);
      children[r]++;
    }
  }
}

void fix_leaf(int u)
{
  int start = node[perm[u]];

  if (start == u) return;      // we are already done

  // move it up to the root
  while (parent[start] != -1) {
    int par = parent[start];
    swaps.emplace_back(label[start], label[par]);
    swap(node[label[start]], node[label[par]]);
    swap(label[start], label[par]);
    start = parent[start];
  }

  // move it down the tree
  stack<pii> S;
  int v = u;
  while (parent[v] != -1) {
    S.emplace(v, parent[v]);
    v = parent[v];
  }
  while (!S.empty()) {
    auto p = S.top();
    S.pop();
    int v1 = p.first, v2 = p.second;
    swaps.emplace_back(label[v1], label[v2]);
    swap(node[label[v1]], node[label[v2]]);
    swap(label[v1], label[v2]);
  }
}

int main()
{
  cin >> n >> m;
  iota(label, label+n, 0);
  iota(node, node+n, 0);
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    u--;  v--;
    G[u].push_back(v);
    G[v].push_back(u);
  }
  
  for (int i = 0; i < n; i++) {
    cin >> perm[i];
    perm[i]--;
  }

  fill(comp, comp+n, -1);
  for (int i = 0; i < n; i++) {
    if (comp[i] == -1) {
      DFS(i, i);
    }
  }

  for (int i = 0; i < n; i++) {
    if (comp[node[perm[i]]] != comp[i]) {
      cout << "impossible" << endl;
      return 0;
    }
  }
  
  for (int i = 0; i < n; i++) {
    if (!children[i]) {
      leaf.push(i);
    }
  }

  while (!leaf.empty()) {
    int curr = leaf.front();
    leaf.pop();

    fix_leaf(curr);

    int par = parent[curr];
    if (par >= 0) {
      if (--children[par] == 0) {
	leaf.push(par);
      }
    }
  }

  cout << swaps.size() << endl;
  for (auto p : swaps) {
    cout << p.first+1 << ' ' << p.second+1 << endl;
  }
  
  return 0;
}
