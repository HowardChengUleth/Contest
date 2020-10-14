#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> pii;

int main()
{
  int N, T;
  cin >> N >> T;

  pii client[10000];
  for (int i = 0; i < N; i++) {
    cin >> client[i].second >> client[i].first;
  }
  sort(client, client+N);
  reverse(client, client+N);

  priority_queue<int> pq;

  int ans = 0;
  int index = 0;
  for (T = 47; T >= 0; T--) {
    while (index < N && client[index].first == T) {
      pq.push(client[index++].second);
    }
    if (pq.size() > 0) {
      ans += pq.top();
      pq.pop();
    }
  }

  cout << ans << endl;
  return 0;
}
