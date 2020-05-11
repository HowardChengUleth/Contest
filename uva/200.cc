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
#include <list>

using namespace std;

typedef int Edge;
typedef list<Edge>::iterator EdgeIter;

struct Graph {
  list<Edge> *nbr;
  int num_nodes;
  Graph(int n)
    : num_nodes(n)
  {
    nbr = new list<Edge>[num_nodes];
  }

  ~Graph()
  {
    delete[] nbr;
  }

  // note: There is no check on duplicate edge, so it is possible to
  // add multiple edges between two vertices
  void add_edge(int u, int v)
  {
    nbr[u].push_front(Edge(v));
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
  string prev;
  cin >> prev;
  
  bool used[26];
  fill(used, used+26, false);
  for (unsigned int i = 0; i < prev.length(); i++) {
    used[prev[i] - 'A'] = true;
  }

  Graph G(26);

  string next;
  while (cin >> next && next != "#") {
    for (unsigned int i = 0; i < next.length(); i++) {
      used[next[i] - 'A'] = true;
    }

    unsigned int i;
    for (i = 0; i < next.length() && i < prev.length() &&
	   prev[i] == next[i]; i++) 
      ;
    if (i < next.length() && i < prev.length()) {
      G.add_edge(prev[i] - 'A', next[i] - 'A');
    }
    prev = next;
  }
  
  vector<int> order;
  topological_sort(G, order);
  for (unsigned int i = 0; i < order.size(); i++) {
    if (used[order[i]]) {
      cout << (char)(order[i] + 'A');
    }
  }
  cout << endl;
  return 0;
}
