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


void mst(int n, int m, Edge elist[])
{
  UnionFind uf(n);

  sort(elist, elist+m);

  int size = 0;
  for (int i = 0; i < m && size < n-1; i++) {
    int c1 = uf.find(elist[i].v1);
    int c2 = uf.find(elist[i].v2);
    if (c1 != c2) {
      uf.merge(c1, c2);
      cout << elist[i].v1+1 << ' ' << elist[i].v2+1 << endl;
    }
  }
}

int main(void)
{ 
   int n;
   cin >> n;

   Edge* elist = new Edge[n*n];
   int k = 0;
   for (int i = 0; i < n; i++) {
     for (int j = 0; j < n; j++) {
       int w;
       cin >> w;
       if (i < j) {
	 elist[k++] = Edge(i, j, w);
       }
     }
   }
   
   mst(n, k, elist);
   return 0;
}



