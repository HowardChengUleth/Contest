#include <iostream>
#include <algorithm>

using namespace std;

int digsum(int n)
{
  int ans = 0;
  while (n > 0) {
    ans += n % 10;
    n /= 10;
  }
  return ans;
}

bool smith(int n)
{
  int d1 = digsum(n);
  int d2 = 0;
  bool prime = true;

  if (n == 2) return false;
  
  while (n % 2 == 0) {
    d2 += 2;
    n /= 2;
    prime = false;
  }

  for (long long p = 3; p*p <= n; p += 2) {
    while (n % p == 0) {
      d2 += digsum(p);
      n /= p;
      prime = false;
    }
  }

  if (n > 1) {
    d2 += digsum(n);
  }

  return d1 == d2 && !prime;
}

void solve(int x)
{
  x++;
  while (!smith(x))
    x++;

  cout << x << endl;
}

int main()
{
  int n;
  cin >> n;

  while (n--) {
    int x;
    cin >> x;
    solve(x);
  }

  return 0;
}
