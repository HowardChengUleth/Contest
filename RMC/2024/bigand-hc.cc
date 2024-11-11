#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main()
{
  int N, T, L;
  cin >> N >> T >> L;

  priority_queue<ll, vector<ll>, greater<ll>> PQ;
  for (int i = 0; i < N; i++) {
    int t;
    cin >> t;
    PQ.push(t);
  }

  for (int i = 0; i < N-1; i++) {
    auto t1 = PQ.top(); PQ.pop();
    auto t2 = PQ.top(); PQ.pop();
    assert(t1 <= t2);
    PQ.push(t2 + T);
  }

  cout << PQ.top() + L << endl;

  return 0;
}
