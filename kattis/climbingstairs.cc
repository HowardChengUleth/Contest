#include <bits/stdc++.h>

using namespace std;

int main()
{
  int n, r, k;
  cin >> n >> r >> k;

  // to office
  int steps = k;

  // to registration
  steps += abs(k-r);

  // walk up and down
  while (steps < n) {
    steps += 2;
  }

  steps += r;

  cout << steps << endl;
   
  
  

  return 0;
}
