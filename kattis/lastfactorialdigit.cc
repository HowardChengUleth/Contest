#include <bits/stdc++.h>

using namespace std;

int f(int N)
{
  int ans = 1;
  for (int i = 1; i <= N; i++) {
    ans = (ans * i) % 10;
  }
  return ans;
}

int main()
{
  int T;

  cin >> T;
  for (int i = 0; i < T; i++) {
    int N;
    cin >> N;
    cout << f(N) << endl;
  }

  return 0;
}
