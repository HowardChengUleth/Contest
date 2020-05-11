#include <iostream>
#include <algorithm>

using namespace std;

void solve()
{
  int N, K, P;
  cin >> N >> K >> P;
  int t = (K+P) % N;
  if (!t) t = N;
  cout << t << endl;
}

int main()
{
  int T;
  cin >> T;
  for (int i = 1; i <= T; i++) {
    cout << "Case " << i << ": ";
    solve();
  }
  return 0;
}
