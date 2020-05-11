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
  bool operator<(const Edge& e) const { return w > e.w; }

  int v1, v2;          /* two endpoints of edge                */
  double w;            /* weight, can be double instead of int */
};


int trips(Edge elist[], int n, int m, int s, int d, int t)
{
  UnionFind uf(n);

  sort(elist, elist+m);

  int w = 0.0;
  for (int i = 0; i < m && uf.find(s) != uf.find(d); i++) {
    w = elist[i].w;
    uf.merge(elist[i].v1, elist[i].v2);
  }

  int ans = t / (w-1);
  if (t % (w-1)) ans++;
  return ans;
}

int main(void)
{
  int N, R;
  Edge elist[100*99/2];
  int num = 1;

  while (cin >> N >> R && (N || R)) {
    for (int i = 0; i < R; i++) {
      cin >> elist[i].v1 >> elist[i].v2 >> elist[i].w;
      elist[i].v1--;
      elist[i].v2--;
    }
    int S, D, T;
    cin >> S >> D >> T;
    S--;
    D--;
    
    cout << "Scenario #" << num++ << endl;
    cout << "Minimum Number of Trips = " << trips(elist, N, R, S, D, T)
	 << endl;
    cout << endl;
  }

  return 0;
}



