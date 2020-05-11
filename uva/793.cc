/* @JUDGE_ID: 1102NT 793 C++ "" */

// UnionFind class -- based on Howard Cheng's C code for UnionFind
// Modified to use C++ by Rex Forsyth, Oct 22, 2003
//
// Constuctor -- builds a UnionFind object of size n and initializes it
// find -- return index of x in the UnionFind; if not found, x is added
// merge -- updates relationship between x and y in the UnionFind

#include <iostream>
#include <string>
#include <sstream>

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

int main(void)
{
  int cases;
  string s;

  cin >> cases;
  getline(cin, s);
  getline(cin, s);
    
  while (cases-- > 0) {
    int n;

    cin >> n;
    getline(cin, s);
    UnionFind uf(n);

    int n1 = 0, n2 = 0;

    while (getline(cin, s) && s != "") {
      istringstream ss(s);
      char c;
      int a, b;
      ss >> c >> a >> b;
      if (c == 'c') {
	uf.merge(a-1, b-1);
      } else if (c == 'q') {
	if (uf.find(a-1) == uf.find(b-1)) {
	  n1++;
	} else {
	  n2++;
	}
      }
    }
    cout << n1 << "," << n2 << endl;

    if (cases) {
      cout << endl;
    }
  }

  return 0;
}
