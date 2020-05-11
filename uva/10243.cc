#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

int adj[1000][1000];
int deg[1000];
int N;

int ans[2][1000];

int search(int v, int parent, bool parent_has_exit)
{
  if (ans[parent_has_exit ? 1 : 0][v] >= 0) {
    return ans[parent_has_exit ? 1 : 0][v];
  }

  // try to put an exit at v
  int best = 1;
  for (int i = 0; i < deg[v]; i++) {
    int w = adj[v][i];
    if (w == parent) continue;
    best += search(w, v, true);
  }
  
  // try to not put an exit at v
  if (parent_has_exit) {
    int temp = 0;
    for (int i = 0; i < deg[v]; i++) {
      int w = adj[v][i];
      if (w == parent) continue;
      temp += search(w, v, false);
    }
    best = min(best, temp);
  }

  return ans[parent_has_exit ? 1 : 0][v] = best;
}

bool solve()
{
  cin >> N;
  if (!N) return false;

  for (int i = 0; i < N; i++) {
    cin >> deg[i];
    for (int j = 0; j < deg[i]; j++) {
      cin >> adj[i][j];
      adj[i][j]--;
    }
  }
  
  fill(ans[0], ans[0]+N, -1);
  fill(ans[1], ans[1]+N, -1);

  // if N == 1 then we must put an exit there
  cout << search(0, -1, N != 1) << endl;

  return true;
}

int main(void)
{
  while (solve())
    ;
  return 0;
}
