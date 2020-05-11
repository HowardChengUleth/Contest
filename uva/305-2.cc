#include <iostream>

using namespace std;

bool good(int k, int m)
{
  // at iteration i, there should be k good guys and k-i bad guys
  int n = 2*k;
  int kill = (m-1) % n;
  for (int i = 0; i < k; i++) {
    if (kill < k) {
      // killed a good guy
      return false;
    }

    // at iteration i, there should be k good guys and k-i bad guys
    n--;
    kill = (kill + (m-1)) % n;
  }
  return true;
}

int solve(int k)
{
  int m = k+1;
  while (true) {
    if (good(k, m)) {
      return m;
    }
    m++;
  }
  return -1;
}

int main()
{
  int ans[14];

  for (int k = 1; k < 14; k++) {
    ans[k] = solve(k);
  }

  int k;
  while (cin >> k && k) {
    cout << ans[k] << endl;
  }
  
  return 0;
}
