// UnionFind class -- based on Howard Cheng's C code for UnionFind
// Modified to use C++ by Rex Forsyth, Oct 22, 2003
//
// Constuctor -- builds a UnionFind object of size n and initializes it
// find -- return index of x in the UnionFind; if not found, x is added
// merge -- updates relationship between x and y in the UnionFind

#include <iostream>
#include <string>
#include <map>
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
	    uf[i].rank = 1;
	 }
      }

      ~UnionFind() {
         delete[] uf;
      }

      int find(int x) { return find(uf,x); }        // for client use
      int size(int x) { return uf[find(uf,x)].rank; }
      
      bool merge(int x, int y) {
	 int res1, res2;
	 res1 = find(uf, x);
	 res2 = find(uf, y);
	 if (res1 != res2) {
	    if (uf[res1].rank > uf[res2].rank) {
	       uf[res2].p = res1;
	       uf[res1].rank += uf[res2].rank;
	       uf[res2].rank = uf[res1].rank;
	    }
	    else {
	       uf[res1].p = res2;
	       uf[res2].rank += uf[res1].rank;
	       uf[res1].rank = uf[res2].rank;
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

void solve(void)
{
  map<string,int> name;
  UnionFind uf(100000);
  int num_name = 0;

  int F;
  cin >> F;
  while (F-- > 0) {
    string name1, name2;
    cin >> name1 >> name2;

    if (name.find(name1) == name.end()) {
      name[name1] = num_name++;
    }
    
    if (name.find(name2) == name.end()) {
      name[name2] = num_name++;
    }

    uf.merge(name[name1], name[name2]);
    cout << uf.size(name[name1]) << endl;
  }
}

int main(void)
{
  int T;
  cin >> T;
  while (T-- > 0) {
    solve();
  }

  return 0;
}
