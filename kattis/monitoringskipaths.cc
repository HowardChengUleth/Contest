#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> pii;

vector<int> G[250000];
int n, k, m;

vector<int> route[250000];
bool root[250000];
int depth[250000];

// returns (number of junctions needed, highest depth of exposed path)
// depth = -1 if there is no exposed path
pii f(int r) {
  if (G[r].size() == 0) {
    // leaf node
    int d = -1;
    for (auto s : route[r]) {
      d = max(d, depth[s]);
    }

    // need to cover this node if there is some route that starts and ends
    // at this node.
    return pii(d == depth[r], d);
  }

  // process subtrees
  int stations = 0;
  int exposed = -1;
  for (auto v : G[r]) {
    depth[v] = depth[r]+1;
    auto p = f(v);
    stations += p.first;
    exposed = max(exposed, p.second);
  }

  // decide whether to monitor root
  if (depth[r] == exposed) {
    stations++;
    exposed = -1;
  }

  return pii(stations, exposed);
}

int main()
{
  cin >> n >> k >> m;
  fill(root, root+n, true);
  
  for (int i = 0; i < k; i++) {
    int u, v;
    cin >> u >> v;
    u--; v--;
    G[u].push_back(v);
    root[v] = false;
  }

  for (int i = 0; i < m; i++) {
    int s, t;
    cin >> s >> t;
    s--; t--;
    route[t].push_back(s);
  }

  int ans = 0;
  for (int i = 0; i < n; i++) {
    if (root[i]) {
      ans += f(i).first;
    }
  }

  cout << ans << endl;
  

  return 0;
}
