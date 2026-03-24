#include <bits/stdc++.h>

using namespace std;

/**
 * Author: chilli
 * Date: 2019-04-26
 * License: CC0
 * Source: https://cp-algorithms.com/graph/dinic.html
 * Description: Flow algorithm with complexity $O(VE\log U)$ where $U = \max |\text{cap}|$.
 * $O(\min(E^{1/2}, V^{2/3})E)$ if $U = 1$; $O(\sqrt{V}E)$ for bipartite matching.
 * Status: Tested on SPOJ FASTFLOW and SPOJ MATCHING, stress-tested
 */

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

struct Dinic {
	struct Edge {
		int to, rev;
		ll c, oc;
		ll flow() { return max(oc - c, 0LL); } // if you need flows
	};
	vi lvl, ptr, q;
	vector<vector<Edge>> adj;
	Dinic(int n) : lvl(n), ptr(n), q(n), adj(n) {}
	void addEdge(int a, int b, ll c, ll rcap = 0) {
		adj[a].push_back({b, sz(adj[b]), c, c});
		adj[b].push_back({a, sz(adj[a]) - 1, rcap, rcap});
	}
	ll dfs(int v, int t, ll f) {
		if (v == t || !f) return f;
		for (int& i = ptr[v]; i < sz(adj[v]); i++) {
			Edge& e = adj[v][i];
			if (lvl[e.to] == lvl[v] + 1)
				if (ll p = dfs(e.to, t, min(f, e.c))) {
					e.c -= p, adj[e.to][e.rev].c += p;
					return p;
				}
		}
		return 0;
	}
	ll calc(int s, int t) {
		ll flow = 0; q[0] = s;
		rep(L,0,31) do { // 'int L=30' maybe faster for random data
			lvl = ptr = vi(sz(q));
			int qi = 0, qe = lvl[s] = 1;
			while (qi < qe && !lvl[t]) {
				int v = q[qi++];
				for (Edge e : adj[v])
					if (!lvl[e.to] && e.c >> (30 - L))
						q[qe++] = e.to, lvl[e.to] = lvl[v] + 1;
			}
			while (ll p = dfs(s, t, LLONG_MAX)) flow += p;
		} while (lvl[t]);
		return flow;
	}
	bool leftOfMinCut(int a) { return lvl[a] != 0; }
};

int n, q, s;

// src = 0, sink = 1
//
// for each time t = 0, 1, ..., n-1
//   "base index": t * (2q+2) + 2
//   download link: 0 (IN) and 1 (OUT)
//   queue i = 0, 1, ..., q-1: 2*i+2 (IN) and 2*i+3 (OUT)

const int SRC = 0;
const int SINK = 1;
const int IN = 0;
const int OUT = 1;

int download_node(int t, int out)
{
  return t * (2*q+2) + 2 + out;
}

int queue_node(int t, int index, int out)
{
  return t * (2*q+2) + 2 + 2*index+2 + out;
}

int main()
{
  cin >> n >> q >> s;

  Dinic G(2 + (2*q+2)*n);

  vector<int> dest_queue(s);
  vector<int> queue_size(q);
  
  for (int i = 0; i < s; i++) {
    cin >> dest_queue[i];
    dest_queue[i]--;
  }
  for (int i = 0; i < q; i++) {
    cin >> queue_size[i];
  }

  int total_data = 0;

  for (int t = 0; t < n; t++) {
    int d;
    cin >> d;
    G.addEdge(download_node(t, IN), download_node(t, OUT), d);
    G.addEdge(download_node(t, OUT), SINK, d);

    for (int i = 0; i < q; i++) {
      G.addEdge(queue_node(t, i, IN), queue_node(t, i, OUT), queue_size[i]);
      G.addEdge(queue_node(t, i, OUT), download_node(t, IN), queue_size[i]);
      if (t < n-1) {
	G.addEdge(queue_node(t, i, OUT), queue_node(t+1, i, IN),
		  queue_size[i]);
      }
    }
    
    for (int i = 0; i < s; i++) {
      int a;
      cin >> a;
      total_data += a;
      G.addEdge(SRC, queue_node(t, dest_queue[i], IN), a);
    }
  }

  int f = G.calc(SRC, SINK);
  if (f == total_data) {
    cout << "possible" << endl;
  } else {
    cout << "impossible" << endl;
  }
  

  return 0;
}
