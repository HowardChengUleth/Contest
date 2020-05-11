#include <bits/stdc++.h>

using namespace std;

int main()
{
  int N, k;
  cin >> N;

  int sum = 0;
  while (N--) {
    cin >> k;
    if (k < 0) {
      sum += -k;
    }
  }
  cout << sum << endl;
  return 0;
}
