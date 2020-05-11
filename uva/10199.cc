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
 */

#include <iostream>
#include <stack>
#include <algorithm>
#include <vector>
#include <string>
#include <cassert>

using namespace std;

vector<string> names;
vector<string> art_pts;

/* maximum number of nodes, maximum degree, and maximum number of edges */
const int MAX_N = 100;
const int MAX_DEG = 100;

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
	/* new bicomponent */
	while (v_stack.top() != v || w_stack.top() != w) {
	  v_stack.pop();
	  w_stack.pop();
	}
	v_stack.pop();
	w_stack.pop();

	if (pred != -1) {
	  art_pts.push_back(names[v]);
	}
      } else {
	G[v].back = min(G[v].back, G[w].back);
      }
    } else {
      /* w has been examined already */
      G[v].back = min(G[v].back, G[w].dfs);
    }
  }
  if (pred == -1 && child > 1) {
    art_pts.push_back(names[v]);
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
  for (int i = 0; i < n; i++) {
    if (G[i].dfs) continue;
    do_dfs(G, i, -1, v_stack, w_stack);
  }
}


int main(void)
{
  int n;
  int id = 1;
  while (cin >> n && n) {
    if (id > 1) {
      cout << endl;
    }
    cout << "City map #" << id++ << ": ";
    names.resize(n);
    for (int i = 0; i < n; i++) {
      cin >> names[i];
    }

    Node G[MAX_N];
    clear_graph(G, n);
    
    int m;
    cin >> m;
    while (m--) {
      string name1, name2;
      cin >> name1 >> name2;
      int u = find(names.begin(), names.end(), name1) - names.begin();
      int v = find(names.begin(), names.end(), name2) - names.begin();
      add_edge(G, u, v);
    }
    art_pts.clear();
    bicomp(G, n);

    sort(art_pts.begin(), art_pts.end());
    art_pts.resize(unique(art_pts.begin(), art_pts.end()) - art_pts.begin());
    cout << art_pts.size() << " camera(s) found" << endl;
    for (int i = 0; i < art_pts.size(); i++) {
      cout << art_pts[i] << endl;
    }
  }

  return 0;
}
