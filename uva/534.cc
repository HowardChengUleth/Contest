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


double distance(int n, int m, Edge elist[])
{
  UnionFind uf(n);

  sort(elist, elist+m);

  double w = 0.0;
  for (int i = 0; i < m && uf.find(0) != uf.find(1); i++) {
    uf.merge(elist[i].v1, elist[i].v2);
    w = elist[i].w;
  }

  return w;
}

int main(void)
{
   cout << fixed << setprecision(3);

   int n;
   int scenario = 1;

   while (cin >> n && n > 0) {
     double x[200], y[200];
     
     for (int i = 0; i < n; i++) {
       cin >> x[i] >> y[i];
     }
   
     Edge elist[200*199/2];
     int k = 0;

     for (int i = 0; i < n; i++) 
       for (int j = i+1; j < n; j++) 
	 elist[k++] = Edge(i,j,hypot(x[i]-x[j], y[i]-y[j]) );

     cout << "Scenario #" << scenario++ << endl;
     cout << "Frog Distance = " << distance(n, k, elist) << endl << endl;
   }
   return 0;
}



