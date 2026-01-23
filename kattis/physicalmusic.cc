#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void solve()
{
  int N;
  cin >> N;

  int P[100000];
  for (int i = 0; i < N; i++) {
    cin >> P[N-1-i];
  }

  vector<int> ans;
  int last = P[0];
  for (int i = 1; i < N; i++) {
    if (P[i] > last) {
      ans.push_back(P[i]);
    }

    last = min(P[i], last);
  }

  sort(ans.begin(), ans.end());
  cout << ans.size() << endl;
  for (auto x : ans) {
    cout << x << endl;
  }

}

int main()
{
  int T;
  cin >> T;
  while (T--)
    solve();

  return 0;
}
