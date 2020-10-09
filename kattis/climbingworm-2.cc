#include <bits/stdc++.h>

using namespace std;

int main()
{
  // d*a - (d-1)*b >= h
  // d*(a-b) >= h-b
  // d >= (h-b) / (a-b)

  int a, b, h;
  cin >> a >> b >> h;

  cout << max(1, ((h-b) + (a-b-1)) / (a-b)) << endl;

  
  return 0;
}
