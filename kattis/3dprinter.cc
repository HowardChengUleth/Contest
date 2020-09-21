#include <bits/stdc++.h>

using namespace std;

int main()
{
  int n;
  cin >> n;

  int num = 1;
  int best = 100000;
  
  for (int d = 0; num <= n; d++) {
    best = min(best, d + (n + (num-1)) / num);
    num *= 2;
  }

  cout << best << endl;
  
  return 0;
}
