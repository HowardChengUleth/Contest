#include <bits/stdc++.h>

using namespace std;

bool solve()
{
  int N;
  cin >> N;
  if (N == 0) {
    return false;
  }

  int64_t primes[10];
  for (int i = 0; i < N; i++) {
    cin >> primes[i];
  }

  int X, Y;
  cin >> X >> Y;

  priority_queue<int64_t, vector<int64_t>, greater<int64_t>> PQ;
  PQ.push(1);

  vector<int64_t> ans;
  
  while (!PQ.empty()) {
    auto curr = PQ.top();
    PQ.pop();

    while (!PQ.empty() && curr == PQ.top()) {
      PQ.pop();
    }

    if (X <= curr && curr <= Y) {
      ans.push_back(curr);
    }

    for (int i = 0; i < N; i++) {
      if (curr * primes[i] <= Y) {
	PQ.push(curr * primes[i]);
      }
    }
  }

  if (ans.size() == 0) {
    cout << "none" << endl;
  } else {
    cout << ans[0];
    for (int i = 1; i < ans.size(); i++) {
      cout << "," << ans[i];
    }
    cout << endl;
  }
  
  return true;
}


int main()
{
  while (solve())
    ;

  return 0;
}
