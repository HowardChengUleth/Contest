#include <bits/stdc++.h>
using namespace std;

#define debug(a) cerr << #a << " = " << (a) << endl;
#define fst first
#define snd second
#define sz(x) (int)(x).size()
#define mp(x, y) make_pair(x, y)
#define all(X) begin(X), end(X)
#define rall(X) rbegin(X), rend(X)

template<typename T, typename U> ostream& operator<<(ostream& o, const pair<T, U>& x) { o << "(" << x.fst << ", " << x.snd << ")"; return o; }
template<typename T> ostream& operator<<(ostream& o, const vector<T>& x) { o << "["; int b = 0; for (auto& a : x) o << (b++ ? ", " : "") << a; o << "]"; return o; }
template<typename T> ostream& operator<<(ostream& o, const set<T>& x) { o << "{"; int b = 0; for (auto& a : x) o << (b++ ? ", " : "") << a; o << "}"; return o; }
template<typename T> ostream& operator<<(ostream& o, const multiset<T>& x) { o << "{"; int b = 0; for (auto& a : x) o << (b++ ? ", " : "") << a; o << "}"; return o; }
template<typename T> ostream& operator<<(ostream& o, const unordered_set<T>& x) { o << "{"; int b = 0; for (auto& a : x) o << (b++ ? ", " : "") << a; o << "}"; return o; }
template<typename T> ostream& operator<<(ostream& o, const unordered_multiset<T>& x) { o << "{"; int b = 0; for (auto& a : x) o << (b++ ? ", " : "") << a; o << "}"; return o; }
template<typename T, typename U> ostream& operator<<(ostream& o, const map<T, U>& x) { o << "{"; int b = 0; for (auto& a : x) o << (b++ ? ", " : "") << a; o << "}"; return o; }
template<typename T, typename U> ostream& operator<<(ostream& o, const multimap<T, U>& x) { o << "{"; int b = 0; for (auto& a : x) o << (b++ ? ", " : "") << a; o << "}"; return o; }
template<typename T, typename U> ostream& operator<<(ostream& o, const unordered_map<T, U>& x) { o << "{"; int b = 0; for (auto& a : x) o << (b++ ? ", " : "") << a; o << "}"; return o; }
template<typename T, typename U> ostream& operator<<(ostream& o, const unordered_multimap<T, U>& x) { o << "{"; int b = 0; for (auto& a : x) o << (b++ ? ", " : "") << a; o << "}"; return o; }

struct Edge;
typedef vector<Edge>::iterator EdgeIter;
struct Edge {
  int to, cap, flow;
  bool is_real;
  pair<int, int> part;
  EdgeIter partner;
  int residual() const { return cap - flow; }
};

struct graph {
  vector<vector<Edge>> nbr;
  int n;
  graph(int n) : nbr(n), n(n) { }
  void add(int u, int v, int cap, int flow, bool is_real, pair<int, int> part) {
    Edge e = {v,cap,flow,is_real,part}; nbr[u].push_back(e);
  }
};

void add_edge(graph& G, int u, int v, int cap) {
  int U = sz(G.nbr[u]), V = sz(G.nbr[v]);
  G.add(u,v,cap,0,true,mp(v,V));
  G.add(v,u,0,0,false,mp(u,U));
}

void push_path(graph& G, int s, int t, const vector<EdgeIter>& path, int flow) {
  for (int i = 0; s != t; s = path[i++]->to) {
    if (path[i]->is_real) { path[i]->flow += flow; path[i]->partner->cap += flow; }
    else { path[i]->cap -= flow; path[i]->partner->flow -= flow; }
  }
} 

int augmenting_path(graph& G, int s, int t, vector<EdgeIter>& path, vector<bool>& visited, int step = 0) {
  if (s==t) return -1;
  visited[s] = 1;
  for (EdgeIter it = begin(G.nbr[s]); it != end(G.nbr[s]); ++it) {
    int v = it->to;
    if (it->residual() > 0 and !visited[v]) {
      path[step] = it;
      int flow = augmenting_path(G, v, t, path, visited, step+1);
      if (flow == -1) return it->residual();
      else if (flow > 0) return min(flow, it->residual());
    }
  }
  return 0;
}

int network_flow(graph& G, int s, int t) {
  for (int i = 0; i < G.n; i++) {
    for (EdgeIter it = G.nbr[i].begin(); it != end(G.nbr[i]); ++it)
      G.nbr[it->part.fst][it->part.snd].partner = it;
  }

  vector<EdgeIter> path(G.n);
  int flow = 0, f;
  do {
    vector<bool> visited(G.n, false);
    if ((f = augmenting_path(G,s,t,path,visited)) > 0) {
      push_path(G, s, t, path, f); flow += f;
    }
  } while (f > 0);
  return flow;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int n, k, m; cin >> n >> k >> m;
  graph G(n*k + 2);
  // void add_edge(graph& G, int u, int v, int cap)
  for (int i = 0, u, v; i < m; i++) {
    cin >> u >> v; u--; v--;
    for (int j = 0; j < k; j++) {
      add_edge(G, n*j + u, n*((j+1) % k) + v, 1);
    }
  }

  int S = n*k, T = n*k + 1;
  for (int i = 0; i < k; i++) {
    add_edge(G, S, n*i + i, 1);
    add_edge(G, n*i + (n-1), T, k);
  }

  cout << network_flow(G, S, T) << endl;
}

