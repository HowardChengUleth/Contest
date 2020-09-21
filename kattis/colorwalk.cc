#include <bits/stdc++.h>

using namespace std;

int n;
int G[2][12][12];
int deg[2][12];

typedef pair<int,int> pii;
vector<pii> G2[12 << 13];
set<int> G2trans[12 << 13];

// the graph's nodes are pairs consisting of the original node and the
// content of the queue
void build_graph(int k)
{
  int N = n << k;
  for (int i = 0; i < N; i++) {
    G2[i].clear();
    G2trans[i].clear();
  }

  for (int u = 0; u < n; u++) {
    for (int s = 0; s < (1 << k); s++) {
      int c = s & 1;
      for (int v = 0; v < n; v++) {
	if (!G[c][u][v]) continue;
	int from = (u << k) + s,
	  to1 = (v << k) + (s >> 1),
	  to2 = (v << k) + (s >> 1) + (1 << (k-1));
	G2[from].emplace_back(to1, to2);
	G2trans[to1].insert(from);
	G2trans[to2].insert(from);
      }
    }
  }
}

bool can_escape(int k)
{
  build_graph(k);

  // do BFS from the trapped states backwards.  The states are the node
  // and the queue content
  
  bool trapped[12 << 13] = {false};
  queue<int> q;
  
  for (int u = 0; u < n; u++) {
    for (int s = 0; s < (1 << k); s++) {
      int v = (u << k) + s;
      int c = s & 1;
      if (!deg[c][u]) {
	trapped[v] = true;
	q.push(v);
      }
    }
  }

  // for each trapped state, look backwards at predecessor and see if there
  // is a way to force Alice into the trapped state.  If the predecessor
  // does not have any other way out, then it is in turn trapped.
  while (!q.empty()) {
    int curr = q.front();
    q.pop();
    for (auto w : G2trans[curr]) {
      if (trapped[w]) continue;
      for (int i = G2[w].size()-1; i >= 0; i--) {
	auto x = G2[w][i];
	if (x.first == curr || x.second == curr) {
	  G2[w].erase(G2[w].begin()+i);
	}
      }
      if (G2[w].empty()) {
	trapped[w] = true;
	q.push(w);
      }
    }
  }

  for (int s = 0; s < (1 << k); s++) {
    if (trapped[s]) {
      return false;
    }
  }
  
  return true;
}

void solve()
{
  cin >> n;
  for (int c = 0; c < 2; c++) {
    for (int i = 0; i < n; i++) {
      deg[c][i] = 0;
      for (int j = 0; j < n; j++) {
	cin >> G[c][i][j];
	if (G[c][i][j]) deg[c][i]++;
      }
    }
  }

  for (int k = 1; k <= n; k++) {
    if (can_escape(k)) {
      cout << k << endl;
      return;
    }
  }
  cout << 0 << endl;
}

int main()
{
  int t;
  cin >> t;
  while (t--) {
    solve();
  }

  return 0;
}
