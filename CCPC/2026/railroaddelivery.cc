//
// 1. if a node can be picked up, then the distance to the closest hub * 2
//    must be <= k.  Note that you don't have to worry about starting from
//    one hub, pick up the node, and go to some other hub because if you can
//    do that, you can also start and end at the closest hub
//
// 2. if one hub is reachable from another in distance <= k, then you can
//    start at either of them.
//
// So algorithm is:
//
// run dijkstra from as multi-source from all hubs, figure out closest
// distance to some hub
//
// merge all hubs using union find
//
// merge all the locations for each equivalent set of hubs

#include <bits/stdc++.h>

using namespace std;

typedef int64_t ll;

/*
 * Dijkstra's Algorithm for sparse graphs
 *
 * Author: Howard Cheng
 *
 * Given a weight matrix representing a graph and a source vertex, this
 * algorithm computes the shortest distance, as well as path, to each
 * of the other vertices.  The paths are represented by an inverted list,
 * such that if v preceeds immediately before w in a path from the
 * source to vertex w, then the path P[w] is v.  The distances from
 * the source to v is given in D[v] (-1 if not connected).
 *
 * Call get_path to recover the path.
 *
 * Note: Dijkstra's algorithm only works if all weight edges are
 *       non-negative.
 *
 * This version works well if the graph is not dense.  The complexity
 * is O((n + m) log (n + m)) where n is the number of vertices and
 * m is the number of edges.
 *
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>
#include <queue>

using namespace std;


// UnionFind class -- based on Howard Cheng's C code for UnionFind
// Modified to use C++ by Rex Forsyth, Oct 22, 2003
//
// Constuctor -- builds a UnionFind object of size n and initializes it
// find -- return index of x in the UnionFind
// merge -- updates relationship between x and y in the UnionFind


class UnionFind
{
      struct UF { int p; int rank; };

   public:
      UnionFind(int n) {          // constructor
	 howMany = n;
	 uf = new UF[howMany];
	 for (int i = 0; i < howMany; i++) {
	    uf[i].p = i;
	    uf[i].rank = 0;
	 }
      }

      ~UnionFind() {
         delete[] uf;
      }

      int find(int x) { return find(uf,x); }        // for client use
      
      bool merge(int x, int y) {
	 int res1, res2;
	 res1 = find(uf, x);
	 res2 = find(uf, y);
	 if (res1 != res2) {
	    if (uf[res1].rank > uf[res2].rank) {
	       uf[res2].p = res1;
	    }
	    else {
	       uf[res1].p = res2;
	       if (uf[res1].rank == uf[res2].rank) {
		  uf[res2].rank++;
	       }
	    }
	    return true;
	 }
	 return false;
      }
      
   private:
      int howMany;
      UF* uf;

      int find(UF uf[], int x) {     // recursive funcion for internal use
	 if (uf[x].p != x) {
	    uf[x].p = find(uf, uf[x].p);
	 }
	 return uf[x].p;
      }
};


struct Edge {
  int to;
  ll weight;       // can be double or other numeric type
  Edge(int t, int w)
    : to(t), weight(w) { }
};
  
typedef vector<Edge>::iterator EdgeIter;

struct Graph {
  vector<Edge> *nbr;
  int num_nodes;
  Graph(int n)
    : num_nodes(n)
  {
    nbr = new vector<Edge>[num_nodes];
  }

  ~Graph()
  {
    delete[] nbr;
  }

  // note: There is no check on duplicate edge, so it is possible to
  // add multiple edges between two vertices
  //
  // If this is an undirected graph, be sure to add an edge both
  // ways
  void add_edge(int u, int v, int weight)
  {
    nbr[u].push_back(Edge(v, weight));
  }
};

typedef pair<int,int> pii;

struct Info
{
  ll dist;
  int u, hub;

  Info(ll dd, int uu, int hh)
    : dist{dd}, u{uu}, hub{hh} { }
  
  // sort from largest to smallest distance
  bool operator<(const Info &info) const
  {
    return dist > info.dist;
  }

};

// closest[i] = hub corresponding to min distance
void dijkstra(const Graph &G, const vector<bool> &hub,
	      vector<ll> &D, vector<int> &closest)
{
  int n = G.num_nodes;
  vector<bool> used(n, false);
  priority_queue<Info> fringe;

  D.resize(n, LLONG_MAX);   // infinity == unreachable
  closest.resize(n);

  for (int i = 0; i < n; i++) {
    if (!hub[i]) continue;
  
    D[i] = 0;
    closest[i] = i;
    fringe.emplace(0, i, i);
  }

  while (!fringe.empty()) {
    Info next = fringe.top();
    fringe.pop();

    int u = next.u;
    if (used[u]) continue;
    used[u] = true;

    for (EdgeIter it = G.nbr[u].begin(); it != G.nbr[u].end(); ++it) {
      int v = it->to;
      ll weight = it->weight + next.dist;

      if (weight < D[v]) {
	D[v] = weight;
	closest[v] = next.hub;
	fringe.emplace(weight, v, next.hub);
      }
    }
  }
}

void mergehub(UnionFind &uf, const Graph &G, const vector<ll> &D,
	      const vector<int> &closest, int k)
{
  // look at all edges u <-> v.  If their closest hub are not the same,
  // then we see if this edge can connect the two hubs

  for (int u = 0; u < G.num_nodes; u++) {
    for (auto e : G.nbr[u]) {
      int v = e.to;
      int hub_u = closest[u];
      int hub_v = closest[v];
      if (hub_u == hub_v)
	continue;
      
      ll len = D[u] + D[v] + e.weight;
      if (len <= k) {
	uf.merge(hub_u, hub_v);
      }
    }
  }
}

int main()
{
  int n, m, h, k;
  cin >> n >> m >> h >> k;

  vector<int> p(n);
  for (auto &x : p) {
    cin >> x;
  }

  vector<bool> hub(n, false);
  for (int i = 0; i < h; i++) {
    int j;
    cin >> j;
    hub[j] = true;
  }

  Graph G(n);
  for (int i = 0; i < m; i++) {
    int u, v, c;
    cin >> u >> v >> c;
    G.add_edge(u, v, c);
    G.add_edge(v, u, c);
  }

  vector<ll> D;
  vector<int> closest;
  dijkstra(G, hub, D, closest);

  UnionFind uf(n);
  mergehub(uf, G, D, closest, k);

  vector<ll> value(n, 0);
  for (int i = 0; i < n; i++) {
    if (D[i] == LLONG_MAX || 2*D[i] > k) {
      // too far to go from closest station and return, so you cannot visit
      //
      // NOTE: there is no need to consider going from hub1 -> i -> hub2
      //       because if distances are different, we should only consider the
      //       closest hub
      continue;
    }
    value[uf.find(closest[i])] += p[i];
  }
  
  int start = max_element(begin(value), end(value)) - begin(value);
  if (value[start]) {
    cout << value[start] << ' ' << start << endl;
  } else {
    cout << "NONE" << endl;
  }
  return 0;
}
