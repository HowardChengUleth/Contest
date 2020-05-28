#include <bits/stdc++.h>

using namespace std;

// to get a spanning tree we can use different algorithms.  I am using
// Kruskal's algorithm to keep connecting unconnected vertices, except
// that I process the edges in arbitrary order because I don't care about
// weights.  To get the maximum degree possible, I start with any vertex
// with max degree and add all its neighbours, and then proceed with the
// rest of Kruskal's algorithm.  No other spanning tree can have a higher
// degree.

vector<int> G[200001];

// UnionFind class -- based on Howard Cheng's C code for UnionFind
// Modified to use C++ by Rex Forsyth, Oct 22, 2003
//
// Constuctor -- builds a UnionFind object of size n and initializes it
// find -- return index of x in the UnionFind
// merge -- updates relationship between x and y in the UnionFind


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

      int find(UF uf[], int x) {     // recursive funcion for internal use
	 if (uf[x].p != x) {
	    uf[x].p = find(uf, uf[x].p);
	 }
	 return uf[x].p;
      }
};


int main()
{
  int n, m;
  cin >> n >> m;

  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    G[u].push_back(v);
    G[v].push_back(u);
  }

  int maxi = 0;
  for (int i = 1; i <= n; i++) {
    if (G[i].size() > G[maxi].size()) {
      maxi = i;
    }
  }

  UnionFind uf(n+1);
  for (auto v : G[maxi]) {
    uf.merge(maxi, v);
    cout << maxi << ' ' << v << endl;
  }
  for (int i = 1; i <= n; i++) {
    for (auto v : G[i]) {
      if (uf.find(v) != uf.find(i)) {
	cout << i << ' ' << v << endl;
	uf.merge(i, v);
      }
    }
  }
  
  return 0;
}
