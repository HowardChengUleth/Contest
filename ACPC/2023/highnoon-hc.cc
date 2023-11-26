#include <bits/stdc++.h>

using namespace std;

int main()
{
  int N, K;
  cin >> N >> K;

  for (int n = 1; n <= N; n++) {
    if (K * ceil(log2(n+1)) <= n) {
      cout << "Good to go!" << endl;
      return 0;
    }
  }

  cout << "Tweak the bounds!" << endl;
  
  return 0;
}
