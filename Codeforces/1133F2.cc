#include <bits/stdc++.h>

using namespace std;

// Of course, if the number of edges from vertex 1 is fewer than D, then it
// is impossible.  If we remove vertex 1 from the graph and the rest separates
// into C connected components, it is also easy to see that it is impossible
// if C > D.
//
// If C <= D, then we check if there is at least one edge from 1 to
// each component.  If so, then there is a solution.  Otherwise no.
//
// If C = D, we just add one edge from 1 to the spanning tree of each
// component and we are done.
//
// If C < D, then we have to add more than 1 edge to some of the components.
// That will create a cycle and we will have to remove some edge from the
// cycle.  Doing this repeatedly is too slow.
//
// Instead, we can just choose D edges from 1 to include in the spanning
// tree based on the observations above.  Then we will run Kruskal's algorithm
// to finish off.  This is almost the same as F1 except that the initial
// cluster is chosen differently.
//

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

typedef pair<int,int> pii;

int main()
{
  int n, m, D;
  cin >> n >> m >> D;

  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    G[u].push_back(v);
    G[v].push_back(u);
  }

  // figure out connected components without v1
  UnionFind uf(n+1);
  for (int i = 2; i <= n; i++) {
    for (auto v : G[i]) {
      if (v == 1) continue;
      uf.merge(i, v);
    }
  }

  // figure out the unique labels
  set<int> CC;
  for (int i = 2; i <= n; i++) {
    if (uf.find(i) == i) {
      CC.insert(i);
    }
  }

  UnionFind uf2(n+1);
  
  // make sure there is an edge from v1 to each component
  set<int> CC2 = CC;
  vector<pii> ans;
  set<int> used;
  for (auto v : G[1]) {
    int label = uf.find(v);
    if (CC2.count(label)) {
      ans.emplace_back(1, v);
      uf2.merge(1, v);
      CC2.erase(label);
      used.insert(v);
    }
  }
  
  if (CC.size() != ans.size() || ans.size() > D) {
    cout << "NO" << endl;
    return 0;
  }

  // now add the remaining edges from v1 to other vertices as needed
  for (auto v : G[1]) {
    if (ans.size() == D) break;
    if (!used.count(v)) {
      ans.emplace_back(1, v);
      uf2.merge(1, v);
    }
  }
  if (ans.size() < D) {
    cout << "NO" << endl;
    return 0;
  }

  for (int i = 2; i <= n; i++) {
    for (auto v : G[i]) {
      if (v != 1 && uf2.find(v) != uf2.find(i)) {
	ans.emplace_back(i, v);
	uf2.merge(i, v);
      }
    }
  }

  cout << "YES" << endl;
  for (auto p : ans) {
    cout << p.first << ' ' << p.second << endl;
  }
  return 0;
}
