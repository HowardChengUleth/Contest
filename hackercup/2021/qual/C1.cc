#include <bits/stdc++.h>

using namespace std;


int N;
int C[50];
vector<int> G[50];
int best[50];     // best[u] = best path from u to any leaf

void DFS(int root, int parent)
{
  best[root] = C[root];
  for (auto child : G[root]) {
    if (child == parent) continue;
    DFS(child, root);
    best[root] = max(best[root], best[child] + C[root]);
  }
}

void solve()
{
  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> C[i];
    G[i].clear();
  }

  for (int i = 0; i < N-1; i++) {
    int A, B;
    cin >> A >> B;
    A--; B--;
    G[A].push_back(B);
    G[B].push_back(A);
  }
  
  DFS(0, -1);
  priority_queue<int> res;
  for (auto child : G[0]) {
    res.push(best[child]);
  }

  int ans = C[0];
  for (int i = 0; i < 2 && !res.empty(); i++) {
    ans += res.top();
    res.pop();
  }
  cout << ans << endl;
}

int main()
{
  int T;
  cin >> T;
  for (int i = 1; i <= T; i++) {
    cout << "Case #" << i << ": ";
    solve();
  }
  return 0;
}
