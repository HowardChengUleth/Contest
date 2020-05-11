// The idea is this:
//
// Every constraint says that if we know the value of one variable,
// the other variable is determined.  So if we form a graph where
// variables are vertices and constraints are edges, we can use
// DFS to push values around:
//
//   1. pick some variable to start
//   2. try one of k values for that variable (loop over it)
//   3. for each value tried, "push" this value to the neighbours and
//      do it recursively.  Whenever we discover something that does
//      not make sense, it means the original value chosen in step 2
//      is bad.  Try another value.
//   4. When we run out of things to push, that means all the variables
//      affected can be set.  Look for any variable that is not
//      yet assigned and repeat.  If we can do everything, say "yes".

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Constraint {
  int a, b, c, i, j;
};

vector<int> graph[1000];
int n, m, k;
Constraint clist[10000];

istream &operator>>(istream &is, Constraint &c)
{
  is >> c.a >> c.i >> c.b >> c.j >> c.c;
  c.i--;
  c.j--;
  return is;
}


bool try_DFS(int v, int *val, int x, bool *seen)
{
  val[v] = x;
  seen[v] = true;

  int w, t;
  for (size_t i = 0; i < graph[v].size(); i++) {
    Constraint &c = clist[graph[v][i]];
    if (v == c.i) {
      w = c.j;
      t = c.c - c.a * val[v];
      if (c.b == 0) {
	if (t) {
	  return false;       // no value for w will work
	} else {
	  continue;           // any value for w will work, so let's not
                              // bother checking 
	}
      }
      if (t % c.b) return false;  // not divisible, impossible to continue
      t /= c.b;
    } else {
      w = c.i;
      t = c.c - c.b * val[v];
      if (c.a == 0) {
	if (t) {
	  return false;       // no value for w will work
	} else {
	  continue;           // any value for w will work, so let's not
                              // bother checking 
	}
      }
      if (t % c.a) return false;  // not divisible, impossible to continue
      t /= c.a;
    }
    if (t < 1 || t > k) return false;  // the other variable is out of range
    if (seen[w] && val[w] != t) return false; // the other variable has already
                                              // been assigned a conflicting
                                              // value
    if (!seen[w] && !try_DFS(w, val, t, seen)) return false;
  }
  return true;
}

bool check_comp(int v, int *val)
{
  int x;
  bool seen[1000];
  
  /* try all the k values */
  for (x = 1; x <= k; x++) {
    fill(seen, seen+n, false);
    if (try_DFS(v, val, x, seen)) {
      return true;
    }
  }
  return false;
}

int main(void)
{
  int cases;

  cin >> cases;
  while (cases-- > 0) {

    cin >> n >> m >> k;
    for (int i = 0; i < n; i++) {
      graph[i].clear();
    }
    for (int i = 0; i < m; i++) {
      cin >> clist[i];
      graph[clist[i].i].push_back(i);
      graph[clist[i].j].push_back(i);
    }

    bool good = true;
    int val[1000];
    fill(val, val+n, 0);         // has not been assigned yet
    for (int i = 0; i < n && good; i++) {
      if (!val[i]) {
	if (!check_comp(i, val)) {
	  good = false;
	}
      }
    }
    cout << (good ? "yes" : "no") << endl;
  }
  return 0;
}
