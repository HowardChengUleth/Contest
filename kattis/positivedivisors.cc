#include <bits/stdc++.h>

using namespace std;

int main()
{
  int64_t N;
  cin >> N;

  set<int64_t> factors;
  factors.insert(1);
  factors.insert(N);

  for (int64_t d = 2; d * d <= N; d++) {
    if (N % d == 0) {
      factors.insert(d);
      factors.insert(N/d);
    }
  }

  for (auto d : factors) {
    cout << d << endl;
  }

  return 0;
}
