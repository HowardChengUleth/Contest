#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int M, N;

bool inside(int r, int c)
{
  return 0 <= r && r < M && 0 <= c && c < N;
}

const int dr[] = { -1, 1, 0, 0 };
const int dc[] = { 0, 0, -1, 1 };

struct Point
{
  int64_t x, y, z;

  Point(string s)
  {
    replace(begin(s), end(s), ',', ' ');
    istringstream iss(s);

    iss >> x >> y >> z;
  }
};

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
      struct UF { int64_t p; int64_t rank; };

   public:
      UnionFind(int64_t n) {          // constructor
	 howMany = n;
	 uf = new UF[howMany];
	 for (int64_t i = 0; i < howMany; i++) {
	    uf[i].p = i;
	    uf[i].rank = 0;
	 }
      }

      ~UnionFind() {
         delete[] uf;
      }

      int64_t find(int64_t x) { return find(uf,x); }        // for client use
      
      bool merge(int64_t x, int64_t y) {
	 int64_t res1, res2;
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
      int64_t howMany;
      UF* uf;

      int64_t find(UF uf[], int64_t x) {             // for internal use
	 if (uf[x].p != x) {
	    uf[x].p = find(uf, uf[x].p);
	 }
	 return uf[x].p;
      }
};

class Edge {

   public:
      Edge(int64_t i=-1, int64_t j=-1, int64_t weight=0) {
	 v1 = i;
	 v2 = j;
	 w = weight;
      }
      bool operator<(const Edge& e) const { return w < e.w; }

      int64_t v1, v2;          /* two endpoints of edge                */
      int64_t w;            /* weight, can be double instead of int */
};

int64_t sqdist(Point a, Point b)
{
  int64_t dx = a.x - b.x, dy = a.y - b.y, dz = a.z - b.z;
  return dx*dx + dy*dy + dz*dz;
}

int main()
{
  vector<Point> A;
  string line;
  while (getline(cin, line)) {
    Point p(line);
    A.push_back(p);
  }

  N = A.size();
  vector<Edge> elist;
  for (int i = 0; i < N; i++) {
    for (int j = i+1; j < N; j++) {
      elist.emplace_back(i, j, sqdist(A[i], A[j]));
    }
  }
  sort(begin(elist), end(elist));

  UnionFind uf(N);
  const int MAX_CONNECTIONS = 1000;
  for (int i = 0; i < min((int)elist.size(), MAX_CONNECTIONS); i++) {
    uf.merge(elist[i].v1, elist[i].v2);
  }

  vector<int> circ_size(N, 0);
  for (int i = 0; i < N; i++) {
    circ_size[uf.find(i)]++;
  }
  sort(rbegin(circ_size), rend(circ_size));

  int64_t ans = 1;
  for (int i = 0; i < 3; i++) {
    ans *= circ_size[i];
    cout << circ_size[i] << ' ';
  }
  cout << endl;

  cout << ans << endl;
  

  return 0;
}
