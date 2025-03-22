#include <bits/stdc++.h>

using namespace std;

void DFS(int v, vector<int> &label, int currlabel, const vector<vector<int>> &G)
{
  label[v] = currlabel;
  for (auto w : G[v]) {
    if (label[w] == -1) {
      DFS(w, label, currlabel, G);
    }
  }
}

int main()
{
  int N, M;
  cin >> N >> M;

  vector<vector<int>> G(N);
  for (int i = 0; i < M; i++) {
    int a, b;
    cin >> a >> b;
    a--;
    b--;

    G[a].push_back(b);
    G[b].push_back(a);
  }

  vector<int> label(N, -1);
  DFS(0, label, 0, G);

  bool printed = false;
  for (int i = 0; i < N; i++) {
    if (label[i] == -1) {
      cout << i+1 << endl;
      printed = true;
    }
  }

  if (!printed) {
    cout << "Connected" << endl;
  }
  
  return 0;
}
