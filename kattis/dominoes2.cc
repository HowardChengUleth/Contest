#include <bits/stdc++.h>

using namespace std;

void BFS(int v, vector<bool> &label, const vector<vector<int>> &G)
{
  if (label[v])
    return;
  
  queue<int> Q;
  label[v] = true;
  Q.push(v);

  while (!Q.empty()) {
    int curr = Q.front();
    Q.pop();

    for (auto w : G[curr]) {
      if (!label[w]) {
	label[w] = true;
	Q.push(w);
      }
    }
  }
}


void solve()
{
  int N, M, L;
  cin >> N >> M >> L;
		      
  vector<vector<int>> G(N);

  for (int i = 0; i < M; i++) {
    int x, y;
    cin >> x >> y;
    x--;
    y--;

    G[x].push_back(y);
  }

  vector<bool> label(N, false);
  for (int i = 0; i < L; i++) {
    int z;
    cin >> z;
    z--;

    BFS(z, label, G);
  }

  cout << count(begin(label), end(label), true) << endl;
}


int main()
{
  int C;
  cin >> C;

  for (int i = 0; i < C; i++) {
    solve();
  }

  return 0;
}
