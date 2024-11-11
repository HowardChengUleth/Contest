#include <bits/stdc++.h>

using namespace std;

int main()
{
  int N;
  cin >> N;

  vector<int> P(N);
  for (auto &x : P) {
    cin >> x;
  }
  sort(begin(P), end(P));

  int cost = P[0], hi = P.back();
  cout << max(0, cost - hi/2) << endl;

  return 0;
}
