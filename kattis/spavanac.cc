#include <bits/stdc++.h>

using namespace std;

int main()
{
  int H, M;

  cin >> H >> M;

  if (M < 45) {
    H = (H + 23) % 24;
  }
  M = (M + 15) % 60;
  cout << H << ' ' << M << endl;
  return 0;
}
