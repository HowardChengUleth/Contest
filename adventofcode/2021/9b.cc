#include <bits/stdc++.h>

using namespace std;

vector<string> A;
int m, n;

const int dr[] = {-1, 1, 0, 0};
const int dc[] = {0, 0, -1, 1};

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

  string s;
  while (cin >> s) {
    A.push_back(s);
  }

  m = A.size();
  n = A[0].size();

  UnionFind uf(m*n);
  
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      if (A[i][j] == '9') continue;
      for (int d = 0; d < 4; d++) {
	int i2 = i + dr[d], j2 = j + dc[d];
	if (0 <= i2 && i2 < m && 0 <= j2 && j2 < n &&
	    A[i2][j2] != '9') {
	  uf.merge(i*n+j, i2*n+j2);
	}
      }
    }
  }

  map<int,int> freq;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      if (A[i][j] == '9') continue;
      freq[uf.find(i*n+j)]++;
    }
  }

  priority_queue<int> sizes;
  for (auto [id, f] : freq) {
    sizes.push(f);
  }

  int ans = 1;
  for (int i = 0; i < 3; i++) {
    ans *= sizes.top();
    sizes.pop();
  }
  cout << ans << endl;

  return 0;
}
