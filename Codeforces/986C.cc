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

int n, m;

unordered_set<int> S;
bool visited[1 << 23];
int parent[1 << 23];
int label[1 << 23];
int sign = (1 << 22);
UnionFind uf(1 << 22);

void walk_up(int curr)
{
  //  cout << "walk_up " << curr << endl;
  if ((curr & sign) == 0) {
    label[curr] = curr;
  }
  for (int v = parent[curr]; v >= 0; v = parent[v]) {
    if ((v & sign) == 0) {
      uf.merge(v, label[curr]);
      break;
    }
    if (label[v] >= 0) break;
    label[v] = curr;
  }
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> m;

  fill(label, label + (1 << 23), -1);
  fill(parent, parent + (1 << 23), -1);
  int x;
  for (int i = 0; i < m; i++) {
    cin >> x;
    S.insert(x);
  }

  for (auto x : S) {
    if (visited[x]) continue;
    
    stack<int> DFSstack;
    visited[x] = true;
    DFSstack.push(x);
    //    cout << "a pushing " << x << endl;

    while (!DFSstack.empty()) {
      int curr = DFSstack.top();
      DFSstack.pop();
      //      cout << "popping " << curr << endl;
      
      if (sign & curr) {
	// neg

	//	cout << "  neg" << endl;
	for (int i = 0; i < n; i++) {
	  if ((1 << i) & curr) {
	    int next = curr - (1 << i);
	    parent[next] = curr;
	    if (!visited[next]) {
	      visited[next] = true;
	      DFSstack.push(next);
	      //	      cout << "b pushing " << next << endl;
	    } else if (label[next] >= 0) {
	      walk_up(next);
	    }
	  }
	}

	if (S.count(curr - sign) > 0) {
	  int next = curr - sign;
	  parent[next] = curr;
	  if (!visited[next]) {
	    visited[next] = true;
	    DFSstack.push(next);
	    //	    cout << "c pushing " << next << endl;
	  }
	}

      } else {
	walk_up(curr);
	
	// pos
	int next = (((1 << n) - 1) & (~curr)) + sign;
	parent[next] = curr;
	if (!visited[next]) {
	  visited[next] = true;
	  DFSstack.push(next);
	  //	  cout << "d pushing " << next << endl;
	} else if (label[next] >= 0) {
	  walk_up(next);
	}
      }
    }
  }

  int count = 0;
  for (auto x : S) {
    if (uf.find(x) == x) count++;
  }
  cout << count << endl;
  
  return 0;
}
