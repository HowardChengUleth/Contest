#include <bits/stdc++.h>

using namespace std;

int N;

int root;
vector<vector<int>> child;

void read_input()
{
  cin >> N;
  child.resize(N);

  for (int i = 0; i < N; i++) {
    int p;
    cin >> p;
    if (!p) {
      root = i;
    } else {
      child[p-1].push_back(i);
    }
  }
}

int excess(int v, int upperbound)
{
  if (child[v].size() == 0) {
    return 0;
  }

  int extra = 0;
  for (auto c : child[v]) {
    extra += excess(c, upperbound);
  }

  return max(0, (int)child[v].size() + extra - upperbound);
}

int main()
{
  read_input();

  int lo = -1;           // impossible
  int hi = N;           // possible

  while (hi - lo > 1) {
    int mid = (lo + hi) / 2;
    if (excess(root, mid) > 0) {
      lo = mid;
    } else {
      hi = mid;
    }
  }

  cout << hi << endl;
  return 0;
}
