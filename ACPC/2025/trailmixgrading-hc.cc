// Basically we have to merge the mixtures both directly and indirectly, and
// for each combined mixture, keep track of the scores
//
// If we use Union Find (Disjoint Set) data structure, we can easily merge
// all the mixtures.  For each pair, we can easily find out if they are in
// the same mixture.  The ID returned by UnionFind::find can be used to
// identify the group and keep track of the score for that group

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

int main()
{
  int n;
  cin >> n;

  UnionFind uf(n);

  for (int i = 0; i < n; i++) {
    int pi;
    cin >> pi;
    uf.merge(i, pi);
  }

  vector<int> score(n, 0);
  for (int i = 0; i < n; i++) {
    int s, a, b;
    cin >> s >> a >> b;
    if (uf.find(a) == uf.find(b)) {
      score[uf.find(a)] += s;
    }
  }

  cout << *max_element(begin(score), end(score)) << endl;
      
  return 0;
}
