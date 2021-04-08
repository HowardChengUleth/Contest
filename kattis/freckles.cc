#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1000;
const int MAX_M = MAX_N * MAX_N;


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


double mst(int n, int m, Edge elist[], int index[], int& size)
{
  UnionFind uf(n);

  sort(elist, elist+m);

  double w = 0.0;
  size = 0;
  for (int i = 0; i < m && size < n-1; i++) {
    int c1 = uf.find(elist[i].v1);
    int c2 = uf.find(elist[i].v2);
    if (c1 != c2) {
      index[size++] = i;
      w += elist[i].w;
      uf.merge(c1, c2);
    }
  }

  return w;
}

int main()
{
  int cases;
  int n, m, i, j;
  double x[MAX_N], y[MAX_N];
  Edge edge[MAX_M];
  int tree[MAX_N], tree_size;

  cin >> cases;

  while (cases-- > 0) {
    cin >> n;
    for (i = 0; i < n; i++) {
      cin >> x[i] >> y[i];
    }
    m = 0;
    for (i = 0; i < n; i++) {
      for (j = i+1; j < n; j++) {
	edge[m].v1 = i;
	edge[m].v2 = j;
	edge[m].w = sqrt((x[i]-x[j])*(x[i]-x[j]) + (y[i]-y[j])*(y[i]-y[j]));
	m++;
      }
    }
    cout << fixed << setprecision(2) << mst(n, m, edge, tree, tree_size)
	 << endl;
    
    if (cases > 0) {
      cout << endl;
    }
  }

  return 0;
}
