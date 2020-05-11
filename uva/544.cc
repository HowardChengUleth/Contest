#include <cmath>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cassert>
#include <algorithm>
#include <map>
#include <string>

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
  bool operator<(const Edge& e) const { return w > e.w; }

  int v1, v2;          /* two endpoints of edge                */
  int w;            /* weight, can be double instead of int */
};


int maxload(int n, int m, Edge elist[], int src, int dest)
{
  UnionFind uf(n);

  sort(elist, elist+m);

  int w = INT_MAX;
  for (int i = 0; i < m && uf.find(src) != uf.find(dest); i++) {
    uf.merge(elist[i].v1, elist[i].v2);
    w = elist[i].w;
  }

  return w;
}

int main(void)
{
  int n, r;
  Edge elist[19900];
  int scenario = 1;

  while (cin >> n >> r && (n || r)) {
    map<string,int> index;
    string src, dest;
    int cities = 0;

    for (int i = 0; i < r; i++) {
      cin >> src >> dest >> elist[i].w;
      if (index.find(src) == index.end()) {
	index[src] = cities++;
      }

      if (index.find(dest) == index.end()) {
	index[dest] = cities++;
      }
      elist[i].v1 = index[src];
      elist[i].v2 = index[dest];
    }
    
    cin >> src >> dest;

    cout << "Scenario #" << scenario++ << endl;
    cout << maxload(n, r, elist, index[src], index[dest]) << " tons" 
	 << endl << endl;
  }

  return 0;
}



