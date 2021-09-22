#include <bits/stdc++.h>

using namespace std;

int f(int x)
{
  int ans = 1;
  while (x) {
    int d = x % 10;
    x /= 10;
    if (d) {
      ans *= d;
    }
  }

  return ans;
}

int main()
{
  int x;
  cin >> x;

  while (x > 9) {
    x = f(x);
  }
  cout << x << endl;
  
  return 0;
}
