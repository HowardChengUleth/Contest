#include <bits/stdc++.h>

using namespace std;

int main()
{
  int N;
  cin >> N;

  vector<int> x(N), y(N);
  for (int i = 0; i < N; i++) {
    cin >> x[i] >> y[i];
  }

  int dx = *max_element(begin(x), end(x)) - *min_element(begin(x), end(x)) + 2;
  int dy = *max_element(begin(y), end(y)) - *min_element(begin(y), end(y)) + 2;
  int ans = 2 * (dx+dy);
  cout << ans << endl;
  return 0;
}
