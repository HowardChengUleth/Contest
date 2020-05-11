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
      Edge(int i=-1, int j=-1, double weight=0) {
	 v1 = i;
	 v2 = j;
	 w = weight;
      }
      bool operator<(const Edge& e) const { return w < e.w; }

      int v1, v2;          /* two endpoints of edge                */
      double w;            /* weight, can be double instead of int */
};


void solve(Edge elist[], int n, int m, int c1, int c2)
{
  UnionFind uf(n);

  sort(elist, elist+m);

  int w;
  for (int i = 0; i < m && uf.find(c1) != uf.find(c2); i++) {
    uf.merge(elist[i].v1, elist[i].v2);
    w = elist[i].w;
  }

  if (uf.find(c1) != uf.find(c2)) {
    cout << "no path" << endl;
  } else {
    cout << w << endl;
  }
}

int main(void)
{
  int C, S, Q;
  int case_num = 1;

  while (cin >> C >> S >> Q && (C || S || Q)) {
    if (case_num > 1) {
      cout << endl;
    }
    cout << "Case #" << case_num++ << endl;
    Edge elist[1000];
    for (int i = 0; i < S; i++) {
      cin >> elist[i].v1 >> elist[i].v2 >> elist[i].w;
      elist[i].v1--;
      elist[i].v2--;
    }

    for (int i = 0; i < Q; i++) {
      int c1, c2;
      cin >> c1 >> c2;
      c1--;
      c2--;
      solve(elist, C, S, c1, c2);
    }

  }
  return 0;
}



