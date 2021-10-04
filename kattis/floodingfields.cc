#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

// Network Flow (Directed and Undirected) -- O(fm) where f = max flow
// To recover flow on an edge, it's in the flow field provided is_real == true.
// Note: if you have an undirected network. simply call add_edge twice
// with an edge in both directions (same capacity).  Note that 4 edges
// will be added (2 real edges and 2 residual edges).  To discover the
// actual flow between two vertices u and v, add up the flow of all
// real edges from u to v and subtract all the flow of real edges from
// v to u.

struct Edge;
typedef vector<Edge>::iterator EdgeIter;

struct Edge {
  int to, cap, flow;
  bool is_real;
  pair<int,int> part;
  EdgeIter partner;
  
  int residual() const { return cap - flow; }
};

struct Graph {
  vector<vector<Edge> > nbr;
  int num_nodes;
  Graph(int n) : nbr(n), num_nodes(n) { }
  
  // No check for duplicate edges!
  // Add (or remove) any parameters that matter for your problem
  void add_edge_directed(int u, int v, int cap, int flow, bool is_real,
			 pair<int,int> part) {
    Edge e = {v,cap,flow,is_real,part};    nbr[u].push_back(e);
  }
};


// Use this instead of G.add_edge_directed in your actual program
void add_edge(Graph& G,int u,int v,int cap){
  //  cout << "adding edge " << u << " -> " << v << endl;
  int U = G.nbr[u].size(), V = G.nbr[v].size();
  G.add_edge_directed(u,v,cap,0,true ,make_pair(v,V));
  G.add_edge_directed(v,u,0  ,0,false,make_pair(u,U));
}

void push_path(Graph& G, int s, int t, const vector<EdgeIter>& path, int flow) {
  for (int i = 0; s != t; s = path[i++]->to)
    if (path[i]->is_real) {
      path[i]->flow += flow;    path[i]->partner->cap += flow;
    } else {
      path[i]->cap -= flow;     path[i]->partner->flow -= flow;
    }
}

int augmenting_path(Graph& G, int s, int t, vector<EdgeIter>& path,
		    vector<bool>& visited, int step = 0) {
  if (s == t) return -1;  visited[s] = true;
  for (EdgeIter it = G.nbr[s].begin(); it != G.nbr[s].end(); ++it) {
    int v = it->to;
    if (it->residual() > 0 && !visited[v]) {
      path[step] = it;
      int flow = augmenting_path(G, v, t, path, visited, step+1);
      if (flow == -1)    return it->residual();
      else if (flow > 0) return min(flow, it->residual());
    }
  }
  return 0;
}

int network_flow(Graph& G, int s, int t) { // note that the graph is modified
  for(int i=0;i<G.num_nodes;i++)
    for(EdgeIter it=G.nbr[i].begin(); it != G.nbr[i].end(); ++it)
      G.nbr[it->part.first][it->part.second].partner = it;
  
  vector<EdgeIter> path(G.num_nodes);
  int flow = 0, f;
  do {
    vector<bool> visited(G.num_nodes, false);
    if ((f = augmenting_path(G, s, t, path, visited)) > 0) {
      push_path(G, s, t, path, f);    flow += f;
    }
  } while (f > 0);
  return flow;
}

int field[100][100];
int n, k, h;

const int dr[5] = {-1, 1, 0, 0, 0};
const int dc[5] = {0, 0, -1, 1, 0};
const int IN = 0, OUT = 1;

int node(int r, int c, int h, int dir)
{
  return 2*(h*n*n + r*n + c) + dir;
}

bool solve()
{
  cin >> n >> k >> h;
  if (!n && !k && !h) return false;

  Graph G(n*n*(h+1)*2+2);

  const int s = 2*n*n*(h+1), t = 2*n*n*(h+1)+1;
  
  for (int r = 0; r < n; r++) {
    for (int c = 0; c < n; c++) {
      cin >> field[r][c];
      for (int k = 0; k <= h; k++) {
	add_edge(G, node(r, c, k, IN), node(r, c, k, OUT), 1);
      }
    }
  }

  for (int i = 0; i < k; i++) {
    int r, c;
    cin >> r >> c;
    add_edge(G, s, node(r, c, 0, IN), 1);
  }

  for (int i = 0; i < h; i++) {
    int level;
    cin >> level;

    for (int r = 0; r < n; r++) {
      for (int c = 0; c < n; c++) {
	if (field[r][c] <= level) continue;
	for (int j = 0; j < 5; j++) {
	  int r2 = r + dr[j], c2 = c + dc[j];
	  if (0 <= r2 && r2 < n && 0 <= c2 && c2 < n) {
	    add_edge(G, node(r2, c2, i, OUT), node(r, c, i+1, IN), 1);
	  }
	}
	if (i == h-1) {
	  add_edge(G, node(r, c, i+1, OUT), t, 1);
	}
      }
    }
  }

  cout << network_flow(G, s, t) << endl;
  
  return true;
}

int main()
{
  solve();
  return 0;
}
