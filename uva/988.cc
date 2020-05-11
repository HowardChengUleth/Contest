#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector< vector<int> > G;

bool read_case(void)
{
  int n;

  if (!(cin >> n)) return false;
  if (!n) return false;

  G.clear();

  while (n-- > 0) {
    vector<int> Gi;
    int m;
    cin >> m;
    while (m-- > 0) {
      int x;
      cin >> x;
      Gi.push_back(x);
    }
    G.push_back(Gi);
  }

  return true;
}

void compute(vector<int> &paths, int v)
{
  if (paths[v] >= 0) {
    return;
  }
  
  if (G[v].size() == 0) {
    paths[v] = 1;
    return;
  }

  paths[v] = 0;
  for (unsigned int i = 0; i < G[v].size(); i++) {
    compute(paths, G[v][i]);
    paths[v] += paths[G[v][i]];
  }
}

void solve_case(void)
{
  vector<int> paths(G.size());

  fill(paths.begin(), paths.end(), -1);

  compute(paths, 0);
  cout << paths[0] << endl;
}

int main(void)
{
  bool first = true;

  while (read_case()) {
    if (!first) {
      cout << endl;
    }
    solve_case();
    first = false;
  }
  return 0;
}
