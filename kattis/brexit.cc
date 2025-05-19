#include <bits/stdc++.h>

using namespace std;

int main()
{
  int C, P, X, L;

  cin >> C >> P >> X >> L;

  vector<vector<int>> G(C+1);
  vector<int> nbr_left(C+1, 0);
  vector<bool> stay(C+1, true);
  for (int i = 0; i < P; i++) {
    int A, B;
    cin >> A >> B;
    
    G[A].push_back(B);
    G[B].push_back(A);
  }

  queue<int> leaving;
  leaving.push(L);
  stay[L] = false;
  while (!leaving.empty()) {
    int v = leaving.front();
    leaving.pop();

    for (auto w : G[v]) {
      if (!stay[w]) continue;
      nbr_left[w]++;
      if (nbr_left[w]*2 >= G[w].size()) {
	leaving.push(w);
	stay[w] = false;
      }
    }
  }

  if (stay[X]) {
    cout << "stay" << endl;
  } else {
    cout << "leave" << endl;
  }
  
  return 0;
}
