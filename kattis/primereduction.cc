#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int step(int n)
{
  int ans = 0;
  for (ll p = 2; p*p <= n; p++) {
    while (n % p == 0) {
      ans += p;
      n /= p;
    }
  }
  if (n > 1) {
    ans += n;
  }
  
  return ans;
}

void solve(int n)
{
  int next;
  int times = 0;
  
  next = step(n);
  times++;
  while (next != n) {
    n = next;
    next = step(n);
    times++;
  }

  cout << next << ' ' << times << endl;
}

int main()
{
  int n;
  while (cin >> n && n != 4) {
    solve(n);
  }
  
  return 0;
}
