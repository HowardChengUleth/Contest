/* @JUDGE_ID: 1102NT 615 C++ "" */

#include <iostream>
#include <map>
#include <set>
#include <list>

using namespace std;

void DFS(int root, map<int,list<int> >& to, set<int>& visited)
{
  visited.insert(root);
  for (list<int>::iterator p = to[root].begin(); p != to[root].end(); p++) {
    DFS(*p, to, visited);
  }
}

int main(void)
{
  int u, v;
  int cases = 1;

  while (cin >> u >> v && (u != -1 && v != -1)) {
    map<int,int> from;
    map<int,list<int> > to;
    bool bad = false;
    while (u && v) {
      from[u];
      bad |= (from[v] != 0);
      from[v] = u;
      to[u].push_back(v);
      cin >> u >> v;
    }

    map<int,int>::iterator p;
    int root = 0;
    for (p = from.begin(); p != from.end(); p++) {
      if (p->second == 0) {
	bad |= (root != 0);
        root = p->first;
      }
    }

    if (!bad) {
      set<int> visited;
      DFS(root, to, visited);
      for (p = from.begin(); p != from.end(); p++) {
	bad |= (visited.find(p->first) == visited.end());
      }
    }

    cout << "Case " << cases++ << " is";
    if (bad) {
      cout << " not";
    }
    cout << " a tree." << endl;
  }

  return 0;
}
