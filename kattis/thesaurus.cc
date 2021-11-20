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

int N, M;
map<string,int> ID;

int getID(string s)
{
  if (ID.find(s) == ID.end()) {
    int t = ID.size();
    ID[s] = t;
  }
  return ID[s];
}

int main()
{
  cin >> N >> M;

  vector<string> essay(N);
  for (auto &s : essay) {
    cin >> s;
  }

  UnionFind uf(2*M);
  
  for (int i = 0; i < M; i++) {
    string w1, w2;
    cin >> w1 >> w2;

    int id1 = getID(w1);
    int id2 = getID(w2);
    uf.merge(id1, id2);
  }

  vector<int> len(ID.size(), INT_MAX);
  for (auto [s, i] : ID) {
    int k = uf.find(i);
    len[k] = min(len[k], (int)s.length());
  }

  int ans = 0;
  for (auto s : essay) {
    if (ID.find(s) == ID.end()) {
      ans += s.length();
    } else {
      ans += len[uf.find(ID[s])];
    }
  }

  cout << ans << endl;
  return 0;
}
