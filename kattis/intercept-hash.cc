#include <bits/stdc++.h>

using namespace std;

// first, we want to know which edges can be used.  We compute the
// shortest distances using Dijkstra's algorithm, so that for each v
// we know the distance d(s,v) and d(v,t).  The latter can be computed by
// running Dijkstra from t on the reverse graph.
//
// Now an edge (u,v) can be taken if d(s,u) + w(u,v) + d(v,t) == d(s,t)
//
// Consider the modified graph consisting only of these edges that can
// be taken.  Notice that this is a DAG.
//
// We want to find "critical points" such that all paths from s to t
// must go through these points.
//
// If f(u,v) is the number of paths from u to v in this DAG, then v is
// a critical point iff f(s,t) == f(s,v)*f(v,t).  These numbers can get very
// large so we mod it with a large prime instead for a probabilistic check.

// Graph layout
//  -- Each problem has its own Edge structure.
// If you see "typedef int Edge;" at the top of an algorithm, change
//    vector<vector<Edge> > nbr; --->  vector<vector<int> > nbr;

typedef long long ll;

struct Edge{ int to; ll weight; }; // weight can be double or other numeric type

struct Graph {
  vector<vector<Edge> > nbr;
  int num_nodes;
  Graph(int n) : nbr(n), num_nodes(n) { }
  
  // Does not allow for duplicate edges between u and v.
  //    (Note that if "typedef int Edge;", do not write the ".to")
  void add_edge(int u, int v, ll weight) {
    for(int i=0;i<nbr[u].size();i++) {
      if(nbr[u][i].to == v) {
        // An edge between u and v is already here.
        // Add tie breaking here if necessary (for example, keep the smallest cost).
        nbr[u][i].weight = min(nbr[u][i].weight,weight);
        return;
      } 
    }
    Edge e = {v,weight};    nbr[u].push_back(e);
  }
};

// Dijkstra's Algorithm [Sparse Graphs] (Directed and Undirected) -- O((n+m)*log(n+m))
//  -- Edge weight >= 0.  May use get_path to obtain the path.

typedef vector<Edge>::const_iterator EdgeIter;

const ll MOD = 2147483659LL;

void dijkstra(const Graph &G, int src, vector<ll> &D) {
  typedef pair<ll,int> pii;
  int n = G.num_nodes;
  vector<bool> used(n, false);
  priority_queue<pii, vector<pii>,  greater<pii> > fringe;

  D.resize(n);  fill(D.begin(), D.end(), -1);  

  D[src] = 0;
  fringe.push(make_pair(0, src));

  while (!fringe.empty()) {
    pii next = fringe.top();    fringe.pop();
    int u = next.second;
    if (used[u]) continue;
    used[u] = true;

    for (EdgeIter it = G.nbr[u].begin(); it != G.nbr[u].end(); ++it) {
      ll v = it->to, weight = it->weight + next.first;
      if (used[v]) continue;
      if (D[v] == -1 || weight < D[v]) {
	D[v] = weight;
	fringe.push(make_pair(D[v], v));
      }
    }
  }
}

// Biconnected Components (Undirected Only) -- O(n+m)
//  -- Some articulation points may be processed multiple times.

const int MAX_N = 100000;
set<int> art_pts;

int dfn, dfs[MAX_N], back[MAX_N];
bool root_art(const Graph& G,int v,int k,int child){
  if(child > 1) return true;
  for(int i=k+1;i<G.nbr[v].size();i++)
    if(!dfs[G.nbr[v][i].to]) return true;
  return false;
}

void do_dfs(const Graph& G, int v, int pred, stack<pair<int,int> > &e_stack){
  int child = 0;
  dfs[v] = back[v] = ++dfn;
  for (int i = 0; i < G.nbr[v].size(); i++) {
    int w = G.nbr[v][i].to;
    if (dfs[w] < dfs[v] && w != pred) e_stack.push(make_pair(v,w));
    if (!dfs[w]) {
      do_dfs(G, w, v, e_stack);      child++;
      
      if (back[w] >= dfs[v]) {                       // new biconnected component
	pair<int,int> e,E = make_pair(v,w);
	do{
	  e = e_stack.top(); e_stack.pop();          // e belongs to this component
	} while(e != E);
	
	if(pred != -1 || root_art(G,v,i,child)){
	  art_pts.insert(v);
	}   // v is articulation point
      } else back[v] = min(back[v],back[w]);
    } else back[v] = min(back[v],dfs[w]);
  }
}

void bicomp(const Graph& G) {
  stack<pair<int,int> > e_stack;
  dfn = 0; fill_n(dfs,G.num_nodes,0);
  for (int i=0;i<G.num_nodes;i++) // get rid of loop to process only one component
    if (dfs[i] == 0) do_dfs(G, i, -1, e_stack);
}

int main()
{
  int N, M;
  cin >> N >> M;

  Graph G(N), Grev(N);
  for (int i = 0; i < M; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    G.add_edge(u, v, w);
    Grev.add_edge(v, u, w);
  }

  int s, t;
  cin >> s >> t;

  vector<ll> D, Drev;
  dijkstra(G, s, D);
  dijkstra(Grev, t, Drev);

  Graph G2(N);
  for (int i = 0; i < N; i++) {
    for (auto e : G.nbr[i]) {
      if (D[i] + Drev[e.to] + e.weight == D[t]) {
	G2.add_edge(i, e.to, e.weight);
	G2.add_edge(e.to, i, e.weight);
	//	cout << "adding " << i << " <-> " << e.to << " " << e.weight << endl;
      }
    }
  }
  art_pts.insert(s);
  art_pts.insert(t);
  bicomp(G2);
  
  for (auto v : art_pts) {
    cout << v << ' ';
  }
  cout << endl;


  return 0;
}
