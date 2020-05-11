#include <bits/stdc++.h>

using namespace std;

int main()
{
  int b, k;
  cin >> b >> k;
  b %= 2;
  
  int r = 0;
  for (int i = 0; i < k; i++) {
    int a;
    cin >> a;
    a %= 2;
    r += ((i < k-1) ? b : 1)*a;
    r %= 2;
  }
  cout << (r ? "odd" : "even") << endl;
  return 0;
}
