//
// If we have a directed graph such that (v,w) is an edge if v beats w
// in a head-to-head election, then we just have to start a DFS from
// the given candidate and make sure that all other candidates are
// reachable.
//
#include <iostream>
#include <algorithm>

using namespace std;

void DFS(int votes[101][101], int v, int n, bool visited[101])
{
  visited[v] = true;
  for (int w = 1; w <= n; w++) {
    if (v == w) continue;
    if (visited[w]) continue;
    if (votes[v][w] > votes[w][v]) {
      DFS(votes, w, n, visited);
    }
  }
}

bool do_case()
{
  int n, m, c;
  cin >> n >> m >> c;
  if (!n && !m && !c) return false;
  
  int votes[101][101];
  for (int i = 1; i <= n; i++) {
    fill(votes[i]+1, votes[i]+n+1, 0);
  }
  
  for (int i = 0; i < m; i++) {
    int perm[100];
    for (int j = 0; j < n; j++) {
      cin >> perm[j];
      for (int k = 0; k < j; k++) {
	votes[perm[k]][perm[j]]++;
      }
    }
  }

  bool visited[101];
  fill(visited+1, visited+n+1, false);
  DFS(votes, c, n, visited);
  if (find(visited+1, visited+n+1, false) != visited+n+1) {
    cout << "no" << endl;
  } else {
    cout << "yes" << endl;
  }

  
  return true;
}

int main(void)
{
  while (do_case())
    ;
  return 0;
}
