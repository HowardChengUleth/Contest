/*
 * Topological sort
 *
 * Author: Howard Cheng
 *
 * Given a directed acyclic graph, the topological_sort routine 
 * returns a vector of integers that gives the vertex number (0 to n-1)
 * such that if there is a path from v1 to v2, then v1 occurs earlier
 * than v2 in the order.  Note that the topological sort result is not
 * necessarily unique.
 *
 * topological_sort returns true if there is no cycle.  Otherwise it
 * returns false and the sorting is unsuccessful.
 *
 * The complexity is O(n + m).
 *
 */


#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef int Edge;
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
  void add_edge(int u, int v)
  {
    nbr[u].push_back(Edge(v));
  }
};

bool DFS(const Graph &G, int v, vector<int> &visited, vector<int> &order,
	 int &time)
{
  visited[v] = 2;
  for (EdgeIter it = G.nbr[v].begin(); it != G.nbr[v].end(); ++it) {
    int w = *it;
    if (!visited[w]) {
      if (!DFS(G, w, visited, order, time)) {
	return false;
      }
    } else if (visited[w] == 2) {
      return false;
    }
  }
  order[G.num_nodes-1-(time++)] = v;
  visited[v] = 1;
  return true;
}

bool topological_sort(const Graph &G, vector<int> &order)
{
  order.resize(G.num_nodes);
  vector<int> visited(G.num_nodes, 0);

  int time = 0;
  for (int i = 0; i < G.num_nodes; i++) {
    if (!visited[i]) {
      if (!DFS(G, i, visited, order, time)) {
	return false;
      }
    }
  }
  return true;
}


int main(void)
{
  int n, m;

  while (cin >> n >> m && (n || m)) {
    Graph G(n);
    for (int i = 0; i < m; i++) {
      int u, v;
      cin >> u >> v;
      G.add_edge(u-1, v-1);
    }
    vector<int> order;
    if (topological_sort(G, order)) {
      for (int i = 0; i < n; i++) {
	cout << order[i]+1 << endl;
      }
    } else {
      cout << "IMPOSSIBLE" << endl;
    }
  }
  return 0;
}
