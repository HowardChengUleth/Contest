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



int m, n;
char grid[100][100];

const int dr[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
const int dc[] = { -1, 0, 1, -1, 1, -1, 0, 1 };

bool inside(int r, int c)
{
    return 0 <= r && r < m && 0 <= c && c < n;
}

void DFS(int r, int c)
{
    grid[r][c] = '.';
    for (int d = 0; d < 8; d++) {
	int r2 = r + dr[d], c2 = c + dc[d];
	if (inside(r2, c2) && grid[r2][c2] == '#') {
	    DFS(r2, c2);
	}
    }
}

void solve1()
{
    int count = 0;
    for (int r = 0; r < m; r++) {
	for (int c = 0; c < n; c++) {
	    if (grid[r][c] == '#') {
		DFS(r, c);
		count++;
	    }
	}
    }

    cout << count << endl;
}

int toindex(int r, int c)
{
    return r*n + c;
}

void solve2()
{
    UnionFind uf(m*n);
    for (int r = 0; r < m; r++) {
	for (int c = 0; c < n; c++) {
	    if (grid[r][c] != '#') continue;
	    for (int d = 0; d < 8; d++) {
		int r2 = r + dr[d], c2 = c + dc[d];
		if (inside(r2, c2) && grid[r2][c2] == '#') {
		    uf.merge(toindex(r, c), toindex(r2, c2));
		}
	    }
	}
    }

    int count = 0;
    for (int r = 0; r < m; r++) {
	for (int c = 0; c < n; c++) {
	    if (grid[r][c] == '#' && uf.find(toindex(r, c)) == toindex(r, c)) {
		count++;
	    }
	}
    }

    cout << count << endl;
}

int main()
{
    cin >> m >> n;
    for (int r = 0; r < m; r++) {
	for (int c = 0; c < n; c++) {
	    cin >> grid[r][c];
	}
    }

    solve2();
    
    return 0;
}
