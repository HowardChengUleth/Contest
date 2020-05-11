// This is mostly a graph problem with a number of connectivity checks.
// This solution uses union-find (instead of DFS or BFS) to check
// for connectivity.

#include <iostream>
#include <string>
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

// union find needs a linear index, so convert 2-D index to 1-D
int index(int r, int c, int i, int j)
{
  return i*c+j;
}

// rule1: use union find to make sure all shaded spaces share the same
// label at the end.
bool rule1(char grid[100][100], int r, int c, int numbers[100][100])
{
  // there are only 4 neighbours
  const int di[] = {-1, 1, 0, 0};
  const int dj[] = {0, 0, -1, 1};

  UnionFind uf(r*c);
  int shaded = -1;       // index of any shaded space
  
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      if (grid[i][j] != '#') continue;
      shaded = index(r, c, i, j);
      for (int k = 0; k < 4; k++) {
	int ni = i + di[k];
	int nj = j + dj[k];
	if (!(0 <= ni && ni < r && 0 <= nj && nj < c)) continue;
	if (grid[ni][nj] != '#') continue;

	// both are shaded, connect them
	uf.merge(index(r, c, i, j), index(r, c, ni, nj));
      }
    }
  }

  if (shaded == -1) {
    // no shaded region, so rule 1 is satisfied
    return true;
  }
  
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      if (grid[i][j] != '#') continue;
      if (uf.find(index(r, c, i, j)) != uf.find(shaded)) {
	return false;
      }
    }
  }
  return true;
}

// use union find to connect all unshaded spaces.  For each distinct
// label (of unshaded spaces), count how many spaces belong to it
// and check that there is exactly one numbered cell with the right count.
bool rule2(char grid[100][100], int r, int c, int numbers[100][100])
{
  const int di[] = {-1, 1, 0, 0};
  const int dj[] = {0, 0, -1, 1};

  UnionFind uf(r*c);
  
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      if (grid[i][j] != '.') continue;
      for (int k = 0; k < 4; k++) {
	int ni = i + di[k];
	int nj = j + dj[k];
	if (!(0 <= ni && ni < r && 0 <= nj && nj < c)) continue;
	if (grid[ni][nj] != '.') continue;
	uf.merge(index(r, c, i, j), index(r, c, ni, nj));
      }
    }
  }

  // count sizes of each region
  int size[10000];
  fill(size, size+r*c, 0);
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      if (grid[i][j] != '.') continue;
      size[uf.find(index(r, c, i, j))]++;
    }
  }

  // check all numbered cells
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      if (numbers[i][j] == 0) continue;
      if (size[uf.find(index(r, c, i, j))] != numbers[i][j]) {
	return false;
      }

      // whole region is checked once, setting size to -1 makes sure
      // that if another number is in the region the check will fail
      size[uf.find(index(r, c, i, j))] = -1;
    }
  }
  
  // make sure that all regions are checked: i.e. all regions has a
  // number
  for (int i = 0; i < r*c; i++) {
    if (size[i] > 0) {
      return false;
    }
  }

  return true;
}

// use union find again, but introduce an "outside" cell and make
// sure that all unshaded spaces are connected to the outside
bool rule3(char grid[100][100], int r, int c, int numbers[100][100])
{
  // this time we have 8 neighbours
  const int di[] = {-1, -1, -1, 0, 0, 1, 1, 1};
  const int dj[] = {-1, 0, 1, -1, 1, -1, 0, 1};

  UnionFind uf(r*c+1);    
  const int outside = r*c;

  // connect boundary cells to the outside
  for (int i = 0; i < r; i++) {
    if (grid[i][0] == '.') {
      uf.merge(index(r, c, i, 0), outside);
    }
    if (grid[i][c-1] == '.') {
      uf.merge(index(r, c, i, c-1), outside);
    }
  }

  for (int j = 0; j < c; j++) {
    if (grid[0][j] == '.') {
      uf.merge(index(r, c, 0, j), outside);
    }
    if (grid[r-1][j] == '.') {
      uf.merge(index(r, c, r-1, j), outside);
    }
  }

  // connect unshaded cells
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      if (grid[i][j] != '.') continue;
      for (int k = 0; k < 8; k++) {
	int ni = i + di[k];
	int nj = j + dj[k];
	if (!(0 <= ni && ni < r && 0 <= nj && nj < c)) continue;
	if (grid[ni][nj] != '.') continue;
	uf.merge(index(r, c, i, j), index(r, c, ni, nj));
      }
    }
  }

  // check unshaded cells connected to outside
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      if (grid[i][j] != '.') continue;
      if (uf.find(index(r, c, i, j)) != uf.find(outside)) {
	return false;
      }
    }
  }
  return true;
}

bool rule4(char grid[100][100], int r, int c, int numbers[100][100])
{
  for (int i = 0; i < r-1; i++) {
    for (int j = 0; j < c-1; j++) {
      if (grid[i][j] == '#' && grid[i+1][j] == '#' &&
	  grid[i][j+1] == '#' && grid[i+1][j+1] == '#') {
	return false;
      }
    }
  }
  return true;
}

void do_case(void)
{
  int r, c, d;
  cin >> r >> c >> d;

  int numbers[100][100];
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      numbers[i][j] = 0;
    }
  }
  while (d-- > 0) {
    int rp, cp, n;
    cin >> rp >> cp >> n;
    numbers[rp][cp] = n;
  }
  char grid[100][100];
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      cin >> grid[i][j];
    }
  }

  if (rule1(grid, r, c, numbers) &&
      rule2(grid, r, c, numbers) &&
      rule3(grid, r, c, numbers) &&
      rule4(grid, r, c, numbers)) {
    cout << "solved" << endl;
  } else {
    cout << "not solved" << endl;
  }
}

int main(void)
{
  int t;
  cin >> t;
  while (t-- > 0) {
    do_case();
  }
  return 0;
}
