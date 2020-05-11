/* @JUDGE_ID: 1102NT 247 C++ "" */

#include <iostream>
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

      int find(UF uf[], int x) {     // recursive funcion for internal use
	 if (uf[x].p != x) {
	    uf[x].p = find(uf, uf[x].p);
	 }
	 return uf[x].p;
      }
};


char graph[25][25];
string names[25];
int num_names;

int find_name(const string &s)
{
  int i;
  for (i = 0; i < num_names; i++) {
    if (names[i] == s) {
      return i;
    }
  }
  names[num_names] = s;
  return num_names++;
}

int main(void)
{
  int m, n;
  int cases = 1;

  while (cin >> n >> m && (m || n)) {
    if (cases > 1) {
      cout << endl;
    }
    num_names = 0;
    cout << "Calling circles for data set " << cases++ << ":" << endl;

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
	graph[i][j] = 0;
      }
    }

    for (int i = 0; i < m; i++) {
      string s;
      int u, v;
      cin >> s;
      u = find_name(s);
      cin >> s;
      v = find_name(s);
      graph[u][v] = 1;
    }

    for (int k = 0; k < n; k++) {
      for (int i = 0; i < n; i++) {
	for (int j = 0; j < n; j++) {
	  graph[i][j] |= graph[i][k] && graph[k][j];
	}
      }
    }

    UnionFind uf(n);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
	if (graph[i][j] && graph[j][i]) {
	  uf.merge(i, j);
	}
      }
    }

    for (int i = 0; i < n; i++) {
      bool first = true;
      for (int j = 0; j < n; j++) {
	if (uf.find(j) == i) {
	  if (!first) {
	    cout << ", ";
	  }
	  first = false;
	  cout << names[j];
	}
      }
      if (!first) {
	cout << endl;
      }
    }
  }

  return 0;
}
