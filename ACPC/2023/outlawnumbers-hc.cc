#include <bits/stdc++.h>

using namespace std;

int next(int n)
{
  if (n == 0 || n == 1) return 0;

  int ans = 1;

  // standard loop to find all factors up to sqrt(n)
  for (long long d = 2; d * d <= n; d++) {
    if (n % d == 0) {
      ans += d;

      // add "partner" as long as partner is different
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
    // cycled to the starting number
    if (curr == n) {
      cout << "looking down a barrel" << endl;
      return 0;
    }

    // we cycled, but the starting number is not involved
    if (outlaws.count(curr) > 0) {
      cout << "safe from harm" << endl;
      return 0;
    }

    outlaws.insert(curr);
    curr = next(curr);
  }
  
  return 0;
}
