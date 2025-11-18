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

int index(int i, int j)
{
  return i*50+j;
}

int main()
{
  int r, c;
  cin >> r >> c;

  vector<string> G(r);
  for (int i = 0; i < r; i++) {
    cin >> G[i];
  }

  UnionFind uf(50*50);

  const int di[] = { -1, 1, 0, 0 };
  const int dj[] = { 0, 0, -1, 1 };
  
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      if (G[i][j] == 'W') continue;
      for (int d = 0; d < 4; d++) {
	int i2 = i + di[d];
	int j2 = j + dj[d];
	if (!(0 <= i2 && i2 < r && 0 <= j2 && j2 < c && G[i2][j2] != 'W'))
	  continue;
	uf.merge(index(i, j), index(i2, j2));
      }
    }
  }

  set<int> ID;
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      if (G[i][j] == 'L') {
	ID.insert(uf.find(index(i, j)));
      }
    }
  }

  cout << ID.size() << endl;
  
  return 0;
}
