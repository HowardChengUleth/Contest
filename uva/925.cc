#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <cassert>

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


#include <string>

void DFS(const Graph &G, int v, vector<bool> &visited, vector<int> &order,
	 int &time)
{
  visited[v] = true;
  for (EdgeIter it = G.nbr[v].begin(); it != G.nbr[v].end(); ++it) {
    int w = *it;
    if (!visited[w]) {
      DFS(G, w, visited, order, time);
    }
  }
  order[G.num_nodes-1-(time++)] = v;
}

void topological_sort(const Graph &G, vector<int> &order)
{
  order.resize(G.num_nodes);
  vector<bool> visited(G.num_nodes, false);

  int time = 0;
  for (int i = 0; i < G.num_nodes; i++) {
    if (!visited[i]) {
      DFS(G, i, visited, order, time);
    }
  }
}

void do_case(void)
{
  int k;
  cin >> k;
  
  string course[120]; 
  bool adj[120][120];
  for (int i = 0; i < k; i++) {
    cin >> course[i];
    fill(adj[i], adj[i]+k, false);
  }
  sort(course, course+k);
  
  int j;
  cin >> j;

  Graph G(k);

  for (int i = 0; i < j; i++) {
    string c1, c2;
    int num;
    int i1, i2;
    
    cin >> c1 >> num;
    i1 = find(course, course+k, c1) - course;
    while (num-- > 0) {
      cin >> c2;
      i2 = find(course, course+k, c2) - course;
      //      cerr << "Adding edge " << i2 << " -> " << i1 << " for course "
      //	   << c2 << " -> " << c1 << endl;
      G.add_edge(i2, i1);
      adj[i2][i1] = true;
    }
  }

  vector<int> order;
  topological_sort(G, order);

  for (int kk = 0; kk < k; kk++) {
    for (int ii = 0; ii < k; ii++) {
      for (int jj = 0; jj < k; jj++) {
	adj[ii][jj] |= (adj[ii][kk] && adj[kk][jj]);
      }
    }
  }

  for (int i = k-1; i >= 0; i--) {
    int u = order[i];
    for (int p = 0; p < k; p++) {
      if (!adj[order[p]][u]) continue;
      for (int q = p+1; q < k; q++) {
	if (adj[order[p]][order[q]] && adj[order[q]][u]) {
	  adj[order[p]][u] = false;
	}
      }
    }
  }
  
  for (int i = 0; i < k; i++) {
    int count = 0;
    for (int p = 0; p < k; p++) {
      if (adj[p][i]) {
	count++;
      }
    }
    if (count == 0) continue;
    cout << course[i] << ' ' << count;
    for (int p = 0; p < k; p++) {
      if (adj[p][i]) {
	cout << ' ' << course[p];
      }
    }
    cout << endl;
  }
}

int main(void)
{
  int C;
  cin >> C;
  while (C-- > 0) {
    do_case();
  }
  return 0;
}
