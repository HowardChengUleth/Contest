/*
 * Implementation of Kruskal's Minimum Spanning Tree Algorithm
 *
 * Author: Howard Cheng
 *
 * This is a routine to find the minimum spanning tree.  It takes as
 * input:
 *
 *      n: number of vertices
 *      m: number of edges
 *  elist: an array of edges (if (u,v) is in the list, there is no need
 *         for (v,u) to be in, but it wouldn't hurt, as long as the weights
 *         are the same).
 *
 * The following are returned:
 *
 *  index: an array of indices that shows which edges from elist are in
 *         the minimum spanning tree.  It is assumed that its size is at
 *         least n-1.
 *   size: the number of edges selected in "index".  If this is not
 *         n-1, the graph is not connected and we have a "minimum
 *         spanning forest."
 *
 * The weight of the MST is returned as the function return value.
 * 
 * The run time of the algorithm is O(m log m).
 *
 * Note: the elements of elist may be reordered.
 *
 * Modified by Rex Forsyth using C++  Aug 28, 2003
 * This version defines the unionfind and edge as classes and  provides
 * constructors. The edge class overloads the < operator. So the sort does
 * not use a  * cmp function. It uses dynamic arrays.
 */

#include <cmath>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cassert>
#include <algorithm>
using namespace std;

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

      int find(UF uf[], int x) {             // for internal use
	 if (uf[x].p != x) {
	    uf[x].p = find(uf, uf[x].p);
	 }
	 return uf[x].p;
      }
};

class Edge {

   public:
      Edge(int i=-1, int j=-1, int weight=0) {
	 v1 = i;
	 v2 = j;
	 w = weight;
      }
      bool operator<(const Edge& e) const { return w < e.w; }

      int v1, v2;          /* two endpoints of edge                */
      int w;            /* weight, can be double instead of int */
};


int mst(int n, int m, Edge elist[])
{
  UnionFind uf(n);

  sort(elist, elist+m);

  int w = 0;
  int size = 0;
  for (int i = 0; i < m && size < n-1; i++) {
    int c1 = uf.find(elist[i].v1);
    int c2 = uf.find(elist[i].v2);
    if (c1 != c2) {
      size++;
      w += elist[i].w;
      uf.merge(c1, c2);
    }
  }

  return w;
}

#include <iostream>
#include <string>
#include <algorithm>
#include <queue>

using namespace std;

typedef pair<int,int> pii;

int x, y;
string grid[50];
int ID[50][50];
pii node[101];
int num_node = 0;
int dist[101][101];

const int di[4] = {-1, 1, 0, 0};
const int dj[4] = {0, 0, -1, 1};

void BFS(int src)
{
  int grid_dist[50][50];

  for (int i = 0; i < y; i++) {
    fill(grid_dist[i], grid_dist[i]+x, -1);
  }

  queue<pii> q;
  q.push(node[src]);
  grid_dist[node[src].first][node[src].second] = 0;
  
  while (!q.empty()) {
    pii curr = q.front();
    q.pop();
    int d = grid_dist[curr.first][curr.second];

    for (int k = 0; k < 4; k++) {
      int nexti = curr.first + di[k];
      int nextj = curr.second + dj[k];
      
      if (!(0 <= nexti && nexti < y &&
	    0 <= nextj && (unsigned)nextj < grid[nexti].length())) continue;
      if (grid[nexti][nextj] == '#') continue;
      if (grid_dist[nexti][nextj] < 0) {
	q.push(make_pair(nexti, nextj));
	grid_dist[nexti][nextj] = d+1;
      }
    }
  }

  for (int i = 0; i < num_node; i++) {
    dist[src][i] = grid_dist[node[i].first][node[i].second];
  }
}

void solve_case()
{
  cin >> x >> y;
  cin.ignore(1);

  for (int i = 0; i < y; i++) {
    getline(cin, grid[i]);
  }

  for (int i = 0; i < y; i++) {
    fill(ID[i], ID[i] + 50, -1);
  }

  num_node = 0;
  for (int i = 0; i < y; i++) {
    for (unsigned int j = 0; j < grid[i].length(); j++) {
      if (grid[i][j] == 'S' || grid[i][j] == 'A') {
	ID[i][j] = num_node;
	node[num_node++] = make_pair(i, j);
      }
    }
  }

  for (int i = 0; i < num_node; i++) {
    BFS(i);
  }

  Edge elist[101*101];
  int edgenum = 0;
  for (int i = 0; i < num_node; i++) {
    for (int j = i+1; j < num_node; j++) {
      elist[edgenum++] = Edge(i, j, dist[i][j]);
    }
  }
  cout << mst(num_node, edgenum, elist) << endl;
}

int main(void)
{
  int N;
  cin >> N;
  while (N-- > 0) {
    solve_case();
  }
  return 0;
}
