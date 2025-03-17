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

int getID(map<string,int> &nameID, const string &name)
{
  if (nameID.find(name) != nameID.end()) {
    return nameID[name];
  }
  int oldsize = nameID.size();
  nameID[name] = oldsize;

  return nameID[name];
}

void solve()
{
  int F;
  cin >> F;

  UnionFind uf(2*F);
  map<string,int> nameID;
  vector<int> size(2*F, 1);
  
  for (int i = 0; i < F; i++) {
    string name1, name2;
    cin >> name1 >> name2;

    int id1 = getID(nameID, name1);
    int id2 = getID(nameID, name2);

    int size1 = size[uf.find(id1)];
    int size2 = size[uf.find(id2)];
    
    if (uf.merge(id1, id2)) {
      size[uf.find(id1)] = size1 + size2;
    }
    cout << size[uf.find(id1)] << endl;
  }
}

int main()
{
  int cases;
  cin >> cases;

  for (int i = 0; i < cases; i++) {
    solve();
  }


  return 0;
}
