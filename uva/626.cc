/* @JUDGE_ID: 1102NT 626 C++ "" */

// just try all triples i, j, k, and use a set of vectors to do the sorting
// automatically (and without duplicates)

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <cassert>

using namespace std;

int graph[100][100];
int n;

bool read_case(void)
{
  if (cin >> n) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
	cin >> graph[i][j];
	if (i == j) {
	  // note: the statement doesn't say it, but the people in the
	  // discussion board says that it is assumed a species cannot
	  // consume itself.
	  graph[i][j] = 0;   
	}
      }
    }

    return true;
  } else {
    return false;
  }
}

void rotate(vector< int >& v)
{
  int t;

  if (v[0] >= v[1] && v[1] >= v[2] || v[0] <= v[1] && v[1] <= v[2]) {
    return;
  }
    
  t = v[0]; v[0] = v[1]; v[1] = v[2]; v[2] = t;
  if (v[0] >= v[1] && v[1] >= v[2] || v[0] <= v[1] && v[1] <= v[2]) {
    return;
  }

  t = v[0]; v[0] = v[1]; v[1] = v[2]; v[2] = t;
  if (v[0] >= v[1] && v[1] >= v[2] || v[0] <= v[1] && v[1] <= v[2]) {
    return;
  }

  assert(false);

}

void solve_case(void)
{
  set< vector< int > > mylist;
  vector< int > v(3);

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (!graph[i][j]) continue;
      for (int k = 0; k < n; k++) {
	if (graph[j][k] && graph[k][i]) {
	  v[0] = i+1; v[1] = j+1; v[2] = k+1;
	  rotate(v);
	  mylist.insert(v);
	}
      }
    }
  }


  for (set< vector< int > >::iterator p = mylist.begin();
       p != mylist.end(); p++) {
    for (int i = 0; i < 3; i++) {
      cout << (*p)[i];
      if (i < 2) {
	cout << " ";
      } else {
	cout << endl;
      }
    }
  }
  cout << "total:" << mylist.size() << endl;
}

int main(void)
{
  while (read_case()) {
    solve_case();
    cout << endl;
  }
  return 0;
}
