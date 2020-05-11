/*
 * Biconnected Components
 *
 * Author: Howard Cheng
 * Date: Oct 15, 2004
 *
 * The routine bicomp() uses DFS to find the biconnected components in
 * a graph.  The graph is stored as an adjacency list.  Use clear_graph()
 * and add_edge() to build the graph.
 *
 * Note: This works only on connected graphs.
 *
 * The code simply prints the biconnected components and the articulation
 * points.  Replace the printing code to do whatever is appropriate.
 *
 * NOTE: some articulation points may be printed multiple times.
 *
 *
 */

#include <iostream>
#include <stack>
#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>

using namespace std;

/* maximum number of nodes, maximum degree, and maximum number of edges */
const int MAX_N = 1000;
const int MAX_DEG = 1000;

vector<pair<int,int> > bridges;

struct Node {
  int deg;
  int nbrs[MAX_DEG];
  int dfs, back;
};

int dfn;

void clear_graph(Node G[], int n)
{
  int i;
  for (i = 0; i < n; i++) {
    G[i].deg = 0;
  }
}

void add_edge(Node G[], int u, int v)
{
  G[u].nbrs[G[u].deg++] = v;
  G[v].nbrs[G[v].deg++] = u;
}

void do_dfs(Node G[], int v, int pred, stack<int> &v_stack, 
	    stack<int> &w_stack)
{
  int i, w, child = 0;

  G[v].dfs = G[v].back = ++dfn;
  for (i = 0; i < G[v].deg; i++) {
    w = G[v].nbrs[i];
    if (G[w].dfs < G[v].dfs && w != pred) {
      /* back edge or unexamined forward edge */
      v_stack.push(v);
      w_stack.push(w);
    }
    if (!G[w].dfs) {
      do_dfs(G, w, v, v_stack, w_stack);
      child++;

      /* back up from recursion */
      if (G[w].back >= G[v].dfs) {
	pair<int,int> edge;
	int count = 0;
	
	/* new bicomponent */
	while (v_stack.top() != v || w_stack.top() != w) {
	  edge = make_pair(min(v_stack.top(), w_stack.top()),
			   max(v_stack.top(), w_stack.top()));
	  count++;
	  v_stack.pop();
	  w_stack.pop();
	}
	edge = make_pair(min(v_stack.top(), w_stack.top()),
			 max(v_stack.top(), w_stack.top()));
	count++;
	v_stack.pop();
	w_stack.pop();
	if (count == 1) {
	  bridges.push_back(edge);
	}

      } else {
	G[v].back = min(G[v].back, G[w].back);
      }
    } else {
      /* w has been examined already */
      G[v].back = min(G[v].back, G[w].dfs);
    }
  }
}

void bicomp(Node G[], int n)
{
  int i;
  stack<int> v_stack, w_stack;

  dfn = 0;
  for (i = 0; i < n; i++) {
    G[i].dfs = 0;
  }
  for (i = 0; i < n; i++) {
    if (G[i].dfs == 0) {
      do_dfs(G, i, -1, v_stack, w_stack);
    }
  }
}

int main(void)
{
  int n;
  while (cin >> n) {
    Node G[MAX_N];
    clear_graph(G, n);
    for (int i = 0; i < n; i++) {
      int u;
      cin >> u;

      char dummy;
      int deg;
      cin >> dummy >> deg >> dummy;
      for (int j = 0; j < deg; j++) {
	int v;
	cin >> v;
	if (u < v) {
	  add_edge(G, u, v);
	}
      }
    }

    bridges.clear();
    bicomp(G, n);
    sort(bridges.begin(), bridges.end());
    
    cout << bridges.size() << " critical links" << endl;
    for (int i = 0; i < bridges.size(); i++) {
      cout << bridges[i].first << " - " << bridges[i].second << endl;
    }
    cout << endl;
  }

  return 0;
}
