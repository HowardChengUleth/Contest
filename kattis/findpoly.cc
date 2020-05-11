#include <bits/stdc++.h>

using namespace std;

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



vector<int> G[100*100];

int index(int r, int c)
{
  return r*100+c;
}

int main()
{
  const string sep = "(),;";
  string line;
  string s;

  while (getline(cin, line)) {
    s += line;
  }
  for (auto &c : s) {
    if (sep.find(c) != string::npos) {
      c = ' ';
    }
  }

  UnionFind uf(100*100);
  bool used[100][100] = {false};
  bool poly[100*100] = {false};

  istringstream iss(s);
  int x1, y1, x2, y2;
  while (iss >> x1 >> y1 >> x2 >> y2) {
    int u = index(x1, y1), v = index(x2, y2);
    G[u].push_back(v);
    G[v].push_back(u);
    uf.merge(u, v);
    used[x1][y1] = used[x2][y2] = true;
    poly[index(x1,y1)] = poly[index(x2,y2)] = true;
  }

  int comp = 0;
  
  for (int x = 0; x < 100; x++) {
    for (int y = 0; y < 100; y++) {
      if (!used[x][y]) continue;

      int ind = index(x,y);
      int ci = uf.find(ind);
      if (ci == ind) {
	comp++;
      } else {
	poly[ind] = false;
      }
      poly[ci] &= G[ind].size() == 2;
    }
  }
  
  cout << comp << ' ' << count(poly, poly+100*100, true) << endl;
  

  return 0;
}
