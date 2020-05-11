/* @JUDGE_ID: 34755FC 670 C++ */ 
/* Ben's solution */


#include <iostream>
#include <sstream>
#include <functional>
#include <algorithm>
#include <iterator>
#include <utility> 
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cassert>
using namespace std;

#define MAX_NODE 202
#define MAX_DEG 101

typedef struct {
  int deg;
  int nbrs[MAX_DEG], cap[MAX_DEG], res[MAX_DEG];
} Node;

void clear_graph(Node *graph)
{
  int i;
  
  for (i = 0; i < MAX_NODE; i++) {
    graph[i].deg = 0;
  }
}

void add_edge(Node *graph, int u, int v, int cap)
{
  graph[u].nbrs[graph[u].deg] = v;
  graph[u].cap[graph[u].deg] = cap;
  graph[u].res[graph[u].deg++] = cap;

  /* WARNING: see note in comment at the top */
  graph[v].nbrs[graph[v].deg] = u;
  graph[v].cap[graph[v].deg] = 0;
  graph[v].res[graph[v].deg++] = 0;
}

/* the path is stored in a peculiar way for efficiency:

   Let v(i) be the index of the vertex in the i-th element of the path.
   Then v(i) is computed by graph[v(i-1)].nbrs[path[i]], where
   v(-1) = source vertex.
*/
   
int augmenting_path(Node *graph, int s, int t, int *path, char *visited,
		    int minflow)
{
  int i, v, flow;
  
  if (s == t) {
    return -1;
  }
  for (i = 0; i < graph[s].deg; i++) {
    v = graph[s].nbrs[i];
    if (graph[s].res[i] >= minflow && !visited[v]) {
      path[0] = i;
      visited[v] = 1;
      if ((flow = augmenting_path(graph, v, t, path+1, visited, minflow))) {
	if (flow == -1) {
	  return graph[s].res[i];
	} else {
	  return (flow < graph[s].res[i]) ? flow : graph[s].res[i];
	}
      }
    }
  }
  return 0;
}

void push_path(Node *graph, int s, int t, int *path, int flow)
{
  int v, w;
  int i, j;

  for (v = s, i = 0; v != t; v = w, i++) {
    w = graph[v].nbrs[path[i]];
    graph[v].res[path[i]] -= flow;
    for (j = 0; j < graph[w].deg; j++) {
      if (graph[w].nbrs[j] == v) {
	graph[w].res[j] += flow;
	break;
      }
    }
  }
}

int network_flow(Node *graph, int s, int t)
{
  char visited[MAX_NODE];
  int path[MAX_NODE];
  int flow = 0, f = 1;
  int i, minflow;

  memset(visited, 0, MAX_NODE);
  while (f) {
    minflow = 0;
    for (i = 0; i < graph[s].deg; i++) {
      if (minflow < graph[s].res[i]) {
	minflow = graph[s].res[i];
      }
    }
    if (minflow) { minflow = 1; }
    for (f = 0; minflow; minflow /= 2) {
      memset(visited, 0, MAX_NODE);
      if ((f = augmenting_path(graph, s, t, path, visited, minflow))) {
	push_path(graph, s, t, path, f);
	flow += f;
	break;
      }
    }
  }

  return flow;
}

double dist ( double x1, double y1, double x2, double y2 ) {
  double d1 = x1 - x2, d2 = y1 - y2;
  return sqrt ( d1*d1 + d2*d2 );
}

double dist ( pair<int, int> const & p1, pair<int, int> const & p2 ) {
  return dist ( p1.first, p1.second, p2.first, p2.second );
}

istream & operator >> ( istream & in, pair<int, int> & p ) {
  return ( in >> p.first >> p.second );
}

ostream & operator << ( ostream & out, pair<int, int> const & p ) {
  return ( out << p.first << " " << p.second );
}

ostream & operator << ( ostream & out, Node const & x ) {
  out << "deg: " << x.deg << endl;
  for ( int i = 1; i < x.deg - 1; ++i ) {
    cout << x.nbrs[i] 
	 << "(cap:" << x.cap[i] 
	 << ",res:" << x.res[i] << ") - ";
  }
  cout << x.nbrs[x.deg-1]
       << "(cap:" << x.cap[x.deg-1] 
	 << ",res:" << x.res[x.deg-1] << ")";
  return out;
}

void do_case(void) {
  int n, m; 
  cin >> n >> m;  
  
  pair<int, int> positions[MAX_NODE];
  for ( int i = 0; i < n + m; ++i ) {
    cin >> positions[i];
  }

  /* construct network flow problem: */
  /* where source = n+m, sink = n+m+1 */
  Node graph[MAX_NODE];
  clear_graph ( graph );  
  for ( int i = 0; i < n - 1; ++i ) {
    double d = 2 * dist ( positions[i], positions[i+1] );
    add_edge ( graph, n+m, i, 1 );       /* Source -> Bob */
    for ( int j = n; j < n+m; ++j ) {
      double d1 = dist ( positions[j], positions[i] ),
	d2 = dist ( positions[j], positions[i+1] );      
      if ( d1 + d2 <= d ) {
	add_edge ( graph, i, j, 1 );     /* Bob    -> Place */
      }
    }
  }
  for (int j = n; j < n+m; j++) {
    add_edge(graph, j, n+m+1, 1);
  }
  network_flow ( graph, n+m, n+m+1 );

  /* construct path */
  int c = 1;
  stringstream ss;
  for ( int i = 0; i < n - 1; ++i ) {
    ++c;
    ss << positions[i] <<  " ";
    for ( int j = 0; j < graph[i].deg; ++j ) {
      if ( graph[i].cap[j] && !graph[i].res[j] ) {
	++c;
	ss << positions[graph[i].nbrs[j]] << " ";
	break;
      }
    }
  }
  ss << positions[n-1];
  cout << c << endl << ss.str () << endl;
}

int main(void)
{
  int cases;
  cin >> cases;
  while (cases-- > 0) {
    do_case();
    if (cases > 0) {
      cout << endl;
    }
  }
  return 0;
}

/* @END_OF_SOURCE_CODE */


