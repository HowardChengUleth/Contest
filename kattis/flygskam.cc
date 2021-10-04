// Great Circle distance between two points using Heaverside formula
//
// Author: Howard Cheng
// Reference: http://mathforum.org/library/drmath/view/51879.html
//
// Given two points specified by their latitudes and longitudes, as well
// as the radius of the sphere, return the shortest distance between the
// two points along the surface of the sphere.
//
// latitude should be between -90 to 90 degrees (inclusive), and
// longitude should be between -180 to 180 degrees (inclusive)
//
// There are also routines that will convert between cartesian coordinates
// (x,y,z) and spherical coordinates (latitude, longitude, radius).
//

#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

const double PI = acos(-1.0);

double greatcircle(double lat1, double long1, double lat2, double long2,
		   double radius)
{
  lat1 *= PI/180.0;
  lat2 *= PI/180.0;
  long1 *= PI/180.0;
  long2 *= PI/180.0;
  
  double dlong = long2 - long1;
  double dlat = lat2 - lat1;
  double a = sin(dlat/2)*sin(dlat/2) +
    cos(lat1)*cos(lat2)*sin(dlong/2)*sin(dlong/2);
  return radius * 2 * atan2(sqrt(a), sqrt(1-a));
}

void longlat2cart(double lat, double lon, double radius,
		  double &x, double &y, double &z)
{
  lat *= PI/180.0;
  lon *= PI/180.0;
  x = radius * cos(lat) * cos(lon);
  y = radius * cos(lat) * sin(lon);
  z = radius * sin(lat);
}

void cart2longlat(double x, double y, double z,
		  double &lat, double &lon, double &radius)
{
  radius = sqrt(x*x + y*y + z*z);
  lat = (PI/2 - acos(z / radius)) * 180.0 / PI;
  lon = atan2(y, x) * 180.0 / PI;
}

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


struct Edge {
  int to;
  double weight;       // can be double or other numeric type
  Edge(int t, double w)
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
  void add_edge(int u, int v, double weight)
  {
    nbr[u].push_back(Edge(v, weight));
  }
};

/* assume that D and P have been allocated */
void dijkstra(const Graph &G, int src, vector<double> &D, vector<int> &P)
{
  typedef pair<double,int> pii;

  int n = G.num_nodes;
  vector<bool> used(n, false);
  priority_queue<pii, vector<pii>,  greater<pii> > fringe;

  D.resize(n);
  P.resize(n);
  fill(D.begin(), D.end(), -1);
  fill(P.begin(), P.end(), -1);

  D[src] = 0;
  fringe.push(make_pair(D[src], src));

  while (!fringe.empty()) {
    pii next = fringe.top();
    fringe.pop();
    int u = next.second;
    if (used[u]) continue;
    used[u] = true;

    for (EdgeIter it = G.nbr[u].begin(); it != G.nbr[u].end(); ++it) {
      int v = it->to;
      double weight = it->weight + next.first;
      if (used[v]) continue;
      if (D[v] == -1 || weight < D[v]) {
	D[v] = weight;
	P[v] = u;
	fringe.push(make_pair(D[v], v));
      }
    }
  }
}

int get_path(int v, const vector<int> &P, vector<int> &path)
{
  path.clear();
  path.push_back(v);
  while (P[v] != -1) {
    v = P[v];
    path.push_back(v);
  }
  reverse(path.begin(), path.end());
  return path.size();
}

#include <map>
#include <algorithm>

typedef pair<double,double> pdd;

const double radius = 6381;

int main(void)
{
  int N, M;
  cin >> N >> M;
  Graph G(N);

  string start, end;
  cin >> start >> end;

  map<string,pdd> loc;
  map<string,int> index;
  for (int i = 0; i < N; i++) {
    string city;
    double lat, lon;
    cin >> city >> lat >> lon;
    loc[city] = pdd(lat, lon);
    index[city] = i;
  }

  for (int i = 0; i < M; i++) {
    string c1, c2;
    cin >> c1 >> c2;

    int i1 = index[c1], i2 = index[c2];
    double d = greatcircle(loc[c1].first, loc[c1].second,
			   loc[c2].first, loc[c2].second,
			   radius) + 100;
    G.add_edge(i1, i2, d);
    G.add_edge(i2, i1, d);
  }

  vector<double> D(N);
  vector<int> P(N);
  dijkstra(G, index[start], D, P);
  if (D[index[end]] < 0) {
    cout << -1 << endl;
  } else {
    cout << fixed << setprecision(10) << D[index[end]] << endl;
  }
  
  return 0;
}


