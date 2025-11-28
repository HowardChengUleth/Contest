#include <bits/stdc++.h>

using namespace std;

void process(map<int,priority_queue<int>> &quests, int X)
{
  int64_t ans = 0;

  while (quests.size() > 0) {
    auto it = quests.upper_bound(X);
    if (it == quests.begin())
      break;

    --it;
    auto &pq = it->second;
    ans += pq.top();
    pq.pop();
    X -= it->first;
    if (pq.empty()) {
      quests.erase(it);
    }
  }

  cout << ans << endl;
}

int main()
{
  // indexed by E
  map<int,priority_queue<int>> quests;

  int N;
  cin >> N;
  for (int i = 0; i < N; i++) {
    string cmd;
    cin >> cmd;

    if (cmd == "add") {
      int E, G;
      cin >> E >> G;
      quests[E].push(G);
    } else {
      int X;
      cin >> X;
      process(quests, X);
    }
  }


  return 0;
}
