#include <bits/stdc++.h>

using namespace std;

int next(int n)
{
  if (n == 0 || n == 1) return 0;

  int ans = 1;
  for (long long d = 2; d * d <= n; d++) {
    if (n % d == 0) {
      ans += d;
      if (d != n/d) {
	ans += n/d;
      }
    }
  }
  return ans;
}

int main()
{
  int n;
  cin >> n;
  
  set<int> outlaws;
  outlaws.insert(n);
  int curr = next(n);

  while (true) {
    if (curr == n) {
      cout << "looking down a barrel" << endl;
      return 0;
    }

    if (outlaws.count(curr) > 0) {
      cout << "safe from harm" << endl;
      return 0;
    }

    outlaws.insert(curr);
    curr = next(curr);
  }
  
  return 0;
}
