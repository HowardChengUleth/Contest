//
// Since all edges have distinct weight, it is equivalent to use Kruskal's
// algorithm and see which edges are not added.
//
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

  bool printed = false;
  for (int i = 0; i < m; i++) {
    int c1 = uf.find(elist[i].v1);
    int c2 = uf.find(elist[i].v2);
    if (c1 != c2) {
      uf.merge(c1, c2);
    } else {
      if (printed) cout << ' ';
      cout << elist[i].w;
      printed = true;
    }
  }
  if (printed) {
    cout << endl;
  } else {
    cout << "forest" << endl;
  }
}

bool do_case()
{
  int n, m;
  cin >> n >> m;
  if (!n && !m) return false;

  Edge elist[25000];
  for (int i = 0; i < m; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    elist[i] = Edge(u, v, w);
  }
  mst(n, m, elist);
  return true;
}

int main(void)
{
  while (do_case())
    ;
  return 0;
}



