#include <bits/stdc++.h>

using namespace std;

void DFS(const vector<vector<int>> &G,
	 vector<int> &label, int v, int id)
{
  label[v] = id;
  for (auto w : G[v]) {
    if (label[w] != -1) continue;
    DFS(G, label, w, id);
  }
}

int main()
{
  int N, K;
  cin >> N >> K;

  vector<vector<int>> G(N);
  for (int i = 0; i < K; i++) {
    int a, b;
    cin >> a >> b;
    a--;
    b--;
    G[a].push_back(b);
    G[b].push_back(a);
  }

  vector<int> label(N, -1);
  int id = 0;
  for (int i = 0; i < N; i++) {
    if (label[i] != -1) continue;
    DFS(G, label, i, id++);
  }

  bool good = true;
  for (int i = 0; i < N; i++) {
    good &= label[i] == label[N-i-1];
  }
  if (good) {
    cout << "Yes" << endl;
  } else {
    cout << "No" << endl;
  }
  
  return 0;
}
