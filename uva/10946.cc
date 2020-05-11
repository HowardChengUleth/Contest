#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

// UnionFind class -- based on Howard Cheng's C code for UnionFind
// Modified to use C++ by Rex Forsyth, Oct 22, 2003
//
// Constuctor -- builds a UnionFind object of size n and initializes it
// find -- return index of x in the UnionFind; if not found, x is added
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

struct Entry {
  char name;
  int size;
  
  bool operator<(const Entry &e) const
  {
    if (size != e.size) {
      return size > e.size;
    } else {
      return name < e.name;
    }
  }
};

string map[50];
int holesize[2500];
Entry entry[2500];
int num_entry;
int x, y;

int main(void)
{
  int cases = 1;

  while (cin >> x >> y && (x || y)) {
    cout << "Problem " << cases++ << ":" << endl;
    for (int i = 0; i < x; i++) {
      cin >> map[i];
    }

    UnionFind uf(x*y);
    fill(holesize, holesize+x*y, 0);
    
    int k = 0;
    for (int i = 0; i < x; i++) {
      for (int j = 0; j < y; j++, k++) {
	if (map[i][j] == '.') continue;
	if (i-1 >= 0 && map[i-1][j] == map[i][j]) {
	  uf.merge(k, k-y);
	}
	if (j-1 >= 0 && map[i][j-1] == map[i][j]) {
	  uf.merge(k, k-1);
	}
      }
    }

    k = 0;
    for (int i = 0; i < x; i++) {
      for (int j = 0; j < y; j++, k++) {
	if (map[i][j] == '.') continue;
	holesize[uf.find(k)]++;
      }
    }

    k = num_entry = 0;
    for (int i = 0; i < x; i++) {
      for (int j = 0; j < y; j++, k++) {
	if (holesize[k]) {
	  entry[num_entry].name = map[i][j];
	  entry[num_entry++].size = holesize[k];
	}
      }
    }

    sort(entry, entry+num_entry);
    for (int i = 0; i < num_entry; i++) {
      cout << entry[i].name << " " << entry[i].size << endl;
    }



  }
  return 0;
}
