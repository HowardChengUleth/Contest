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
#include <queue>
#include <string>

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

bool topological_sort(const Graph &G, vector<int> &order)
{
  vector<int> indeg(G.num_nodes);
  fill(indeg.begin(), indeg.end(), 0);
  for (int i = 0; i < G.num_nodes; i++) {
    for (int j = 0; j < G.nbr[i].size(); j++) {
      indeg[G.nbr[i][j]]++;
    }
  }

  // use a priority queue if you want to get a topological sort order
  // with ties broken by lexicographical ordering
  priority_queue<int, vector<int>, greater<int> > q;
  for (int i = 0; i < G.num_nodes; i++) {      
    if (indeg[i] == 0) {
      q.push(i);
    }
  }

  order.clear();
  while (!q.empty()) {
    int v = q.top();
    q.pop();
    order.push_back(v);
    for (int i = 0; i < G.nbr[v].size(); i++) {
      if (--indeg[G.nbr[v][i]] == 0) {
	q.push(G.nbr[v][i]);
      }
    }
  }
   
  return order.size() == G.num_nodes;
}

bool do_case(int id)
{
  int N;
  if (!(cin >> N)) return false;

  string name[100];
  for (int i = 0; i < N; i++) {
    cin >> name[i];
  }

  Graph G(N);

  int M;
  cin >> M;
  for (int i = 0; i < M; i++) {
    string name1, name2;
    cin >> name1 >> name2;
    int u1 = find(name, name+N, name1) - name;
    int u2 = find(name, name+N, name2) - name;
    
    G.add_edge(u1, u2);
  }

  vector<int> order;
  topological_sort(G, order);
  cout << "Case #" << id << ": Dilbert should drink beverages in this order:";
  for (int i = 0; i < N; i++) {
    cout << ' ' << name[order[i]];
  }
  cout << "." << endl << endl;


  return true;
}

int main()
{
  int id = 1;
  while (do_case(id++))
    ;
  return 0;
}

