#include <bits/stdc++.h>

using namespace std;

int n;
vector<int> nbr[100000];


void solve(int root, int parent, bool before_parent = true)
{
  int deg = nbr[root].size();

  // figure out how many go before
  int before = deg / 2;
  if (parent != -1 && !before_parent && before > 0) {
    before--;
  }
  int i = 0;
  while (before) {
    int v = nbr[root][i];
    if (v != parent) {
      solve(v, root, true);
      before--;
    }
    i++;
  }
  cout << root << ' ';
  while (i < deg) {
    int v = nbr[root][i];
    if (v != parent) {
      solve(v, root, false);
    }
    i++;
  }
}

int main()
{
  cin >> n;
  for (int i = 0; i < n-1; i++) {
    int u, v;
    cin >> u >> v;
    nbr[u].push_back(v);
    nbr[v].push_back(u);
  }

  solve(0, -1);

  cout << endl;
  
  return 0;
}
